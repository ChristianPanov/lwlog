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
                backend.args_buffers[arg_count],
                BufferLimits::argument,
                std::forward<Args>(args)
            ), ++arg_count), ...);

            details::format_args_append<BufferLimits>(backend.message_buffer, message,
                backend.args_buffers, arg_lengths, arg_count);
        }

        for (const auto& sink : backend.sink_storage)
        {
            if (sink->should_sink(log_level))
            {
                sink->sink_it({ backend.message_buffer.data(), log_level, meta, 
                    backend.topics, backend.topics.topic_index() });
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
        details::source_meta meta;
        std::string_view message;
        level log_level;

        std::uint16_t args_slot_index{ 0 };
        std::uint8_t arg_count{ 0 };
        std::uint8_t topic_index{ 0 };
    };

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::process_item(
        backend<BufferLimits, ConcurrencyModelPolicy>& backend)
    {
        const auto item{ backend.queue.dequeue() };

        backend.message_buffer.reset();

        if (item.arg_count == 0)
        {
            backend.message_buffer.append(item.message);
        }
        else
        {
            const auto& slot{ backend.arg_buffers_pool.get_slot(item.args_slot_index) };

            details::format_args_append<BufferLimits>(backend.message_buffer, item.message,
                slot.args, slot.lengths, item.arg_count);

            backend.arg_buffers_pool.release_args_buffer(item.args_slot_index);
        }

        for (const auto& sink : backend.sink_storage)
        {
            if (!item.meta.is_initialized())
            {
                sink->sink_it(backend.message_buffer.c_str());
            }
            else if (sink->should_sink(item.log_level))
            {
                sink->sink_it({ backend.message_buffer.data(), item.log_level,
                    item.meta, backend.topics, item.topic_index });
            }
        }
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::init(
        backend<BufferLimits, ConcurrencyModelPolicy>& backend)
    {
        backend.has_work.clear(std::memory_order_release);
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
                    if (backend.has_work.test_and_set(std::memory_order_acquire) || !backend.queue.is_empty())
                    {
                        adaptive_waiter.reset();

                        while (!backend.queue.is_empty())
                        {
                            asynchronous_policy::process_item(backend);
                        }

                        backend.has_work.clear(std::memory_order_release);
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
        if constexpr (sizeof...(args) == 0)
        {
            backend.queue.enqueue(
                meta, 
                message, 
                log_level, 
                static_cast<std::uint16_t>(0), 
                static_cast<std::uint8_t>(0), 
                backend.topics.topic_index()
            );
        }
        else
        {
            const std::uint8_t slot_index{ backend.arg_buffers_pool.acquire_args_buffer() };
            auto& slot{ backend.arg_buffers_pool.get_slot(slot_index) };

            std::uint8_t arg_count{ 0 };

            ((slot.lengths[arg_count] = details::convert_to_chars(
                        slot.args[arg_count],
                        BufferLimits::argument,
                        std::forward<Args>(args)
                    ), ++arg_count), ...);

            backend.queue.enqueue(meta, message, log_level, slot_index, arg_count, backend.topics.topic_index());
        }

        backend.has_work.test_and_set(std::memory_order_release);
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename BufferLimits, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::log(
        backend<BufferLimits, ConcurrencyModelPolicy>& backend, std::string_view message)
    {
        backend.queue.enqueue(
            details::source_meta{}, 
            message, 
            level{}, 
            std::uint16_t{}, 
            std::uint8_t{}, 
            std::uint8_t{}
        );

        backend.has_work.test_and_set(std::memory_order_release);
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