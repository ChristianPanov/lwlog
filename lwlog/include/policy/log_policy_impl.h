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
            details::log_args::captured_args<BufferLimits> captured_args;
            const std::uint8_t arg_count{ details::log_args::capture_args(captured_args, std::forward<Args>(args)...) };

            details::fmt::format_args_typed<BufferLimits>(backend.message_buffer, message, captured_args, arg_count);
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

        details::log_args::captured_args<BufferLimits> captured_args;
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
        details::log_args::capture_args(captured_args, std::forward<Args>(args)...);
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
            details::fmt::format_args_typed<BufferLimits>(backend.message_buffer, item.message, item.captured_args, item.arg_count);
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
                    bool consumed_any{ false };

                    while (backend.queue.try_consume_one(
                        [&backend, &consumed_any](const queue_item_t<BufferLimits, ConcurrencyModelPolicy>& item)
                        {
                            consumed_any = true;
                            asynchronous_policy::process_item(backend, item);
                        }))
                    {}

                    if (consumed_any)
                    {
                        adaptive_waiter.reset();
                    }
                    else
                    {
                        adaptive_waiter.wait();
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
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::log(
        backend<BufferLimits, ConcurrencyModelPolicy>& backend, std::string_view message)
    {
        backend.queue.enqueue(details::source_meta{}, message, level{}, std::uint8_t{});
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