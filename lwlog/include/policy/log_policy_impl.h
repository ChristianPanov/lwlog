#pragma once

namespace lwlog
{
    template<typename BufferLimits, typename ConcurrencyModelPolicy, typename... Args>
    void synchronous_policy::log(backend<BufferLimits, ConcurrencyModelPolicy>& backend, 
        std::string_view message, level log_level, const details::source_meta& meta, Args&&... args)
    {
        backend.message_buffer.reset();

        if constexpr (sizeof...(args) == 0)
        {
            backend.message_buffer.append(message);
        }
        else
        {
            std::uint16_t arg_lengths[BufferLimits::arg_count]{};
            std::uint8_t arg_count{ 0 };

            ((arg_lengths[arg_count] = details::convert_to_chars(
                backend.arguments[arg_count],
                BufferLimits::argument, 
                std::forward<Args>(args)
            ), ++arg_count), ...);

            details::fmt::format_args_append<BufferLimits>(backend.message_buffer, message,
                backend.arguments, arg_lengths, arg_count);
        }

        const details::record<BufferLimits> record{ backend.message_buffer.data(), log_level, meta, 
            backend.topics, backend.topics.topic_index() 
        };

        for (const auto& sink : backend.sink_storage)
        {
            if (sink->should_sink(log_level))
            {
                sink->sink_it(record);
            }
        }
    }

    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    void synchronous_policy::log(backend<BufferLimits, ConcurrencyModelPolicy>& backend, std::string_view message)
    {
        backend.message_buffer.reset();
        backend.message_buffer.append(message);

        for (const auto& sink : backend.sink_storage)
        {
            sink->sink_it(backend.message_buffer.c_str());
        }
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    struct asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::backend<
        BufferLimits, ConcurrencyModelPolicy>::queue_item
    {
        queue_item() = default;
        template<typename... Args>
        queue_item(const details::source_meta& meta, std::string_view message, level log_level,
            std::uint8_t topic_index, Args&&... args);

        details::source_meta meta;
        std::string_view message;
        level log_level;

        std::uint8_t topic_index{ 0 };
        std::uint8_t arg_count{ 0 };

        details::async_args::captured_args<BufferLimits> arguments;
    };

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    template<typename... Args>
    asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::backend<
        BufferLimits, ConcurrencyModelPolicy>::queue_item::queue_item(const details::source_meta& meta, 
            std::string_view message, level log_level, std::uint8_t topic_index, Args&&... args)
        : meta{ meta }
        , message{ message }
        , log_level{ log_level }
        , topic_index{ topic_index }
        , arg_count{ sizeof...(Args) }
    {
        std::uint8_t i{ 0 };
        (arguments.set(i++, std::forward<Args>(args)), ...);
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::process_item(
        backend<BufferLimits, ConcurrencyModelPolicy>& backend, 
        const queue_item_t<BufferLimits, ConcurrencyModelPolicy>& item)
    {
        backend.message_buffer.reset();

        if (item.arg_count == 0)
        {
            backend.message_buffer.append(item.message);
        }
        else
        {
            details::fmt::format_args_typed<BufferLimits>(backend.message_buffer, item.message, item.arguments, item.arg_count);
        }

        if (item.meta.is_initialized())
        {
            const details::record<BufferLimits> record{ backend.message_buffer.data(), item.log_level, item.meta, 
                backend.topics, item.topic_index 
            };

            for (const auto& sink : backend.sink_storage)
            {
                if (sink->should_sink(item.log_level))
                {
                    sink->sink_it(record);
                }
            }
        }
        else
        {
            for (const auto& sink : backend.sink_storage)
            {
                sink->sink_it(backend.message_buffer.c_str());
            }
        }
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::init(
        backend<BufferLimits, ConcurrencyModelPolicy>& backend)
    {
        backend.has_work.store(false, std::memory_order_relaxed);
        backend.shutdown.store(false, std::memory_order_relaxed);

        backend.worker_thread = std::thread([&backend]() 
            {
                if (ThreadAffinity != default_thread_affinity)
                {
                    details::os::set_thread_affinity(ThreadAffinity);
                }

                details::adaptive_waiter<4000, 10000> adaptive_waiter;

                while (!backend.shutdown.load(std::memory_order_relaxed) || !backend.queue.is_empty())
                {
                    const bool signaled{ backend.has_work.exchange(false, std::memory_order_acq_rel) };
                    if (!signaled && backend.queue.is_empty())
                    {
                        adaptive_waiter.wait();
                        continue;
                    }

                    adaptive_waiter.reset();

                    queue_item_t<BufferLimits, ConcurrencyModelPolicy> out_item;
                    while (backend.queue.try_dequeue(out_item))
                    {
                        asynchronous_policy::process_item(backend, out_item);
                    }
                }
            });
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy, typename... Args>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::log(backend<BufferLimits, ConcurrencyModelPolicy>& backend, 
        std::string_view message, level log_level, const details::source_meta& meta, Args&&... args)
    {
        backend.queue.enqueue(meta, message, log_level, backend.topics.topic_index(), std::forward<Args>(args)...);

        backend.has_work.store(true, std::memory_order_release);
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::log(
        backend<BufferLimits, ConcurrencyModelPolicy>& backend, std::string_view message)
    {
        backend.queue.enqueue(details::source_meta{}, message, level{}, std::uint8_t{});

        backend.has_work.store(true, std::memory_order_release);
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::backend<BufferLimits, ConcurrencyModelPolicy>::~backend()
    {
        shutdown.store(true, std::memory_order_relaxed);

        if (worker_thread.joinable())
        {
            worker_thread.join();
        }
    }
}