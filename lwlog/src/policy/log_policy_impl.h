#pragma once

#include "details/memory_buffer.h"

namespace lwlog
{
    template<typename Config, typename BufferLimits, typename ConcurrencyModelPolicy, typename... Args>
    void synchronous_policy::log(backend<Config, BufferLimits, ConcurrencyModelPolicy>& backend,
        const details::topic_registry<typename Config::topic_t>& topic_registry, std::string_view message, 
        level log_level, const details::source_meta& meta, Args&&... args)
    {
        backend.message_buffer.reset();
        backend.message_buffer.append(message);

        const details::record<Config, BufferLimits> record{ 
            backend.message_buffer.c_str(),
            log_level, 
            meta, 
            topic_registry 
        };

        for (const auto& sink : backend.sink_storage)
        {
            if (sink->should_sink(log_level))
            {
                sink->sink_it(record);
            }
        }
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename Config, typename BufferLimits, typename ConcurrencyModelPolicy>
    struct asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::backend<
        Config, BufferLimits, ConcurrencyModelPolicy>::queue_item
    {
        const char*			                                message;
        level						                        log_level;
        details::source_meta		                        meta;
        details::topic_registry<typename Config::topic_t>   topic_registry;

        std::uint8_t args_buffer_index{ 0 };
        bool has_args{ false };
    };

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename Config, typename BufferLimits, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::init(
        backend<Config, BufferLimits, ConcurrencyModelPolicy>& backend)
    {
        backend.shutdown.store(false, std::memory_order_relaxed);
        backend.worker_thread = std::thread([&backend]() 
            {
                if (ThreadAffinity != default_thread_affinity)
                {
                    details::os::set_thread_affinity(ThreadAffinity);
                }

                while (!backend.shutdown.load(std::memory_order_relaxed) || !backend.queue.is_empty())
                {
                    if (!backend.queue.is_empty())
                    {
                        auto& item{ backend.queue.dequeue() };

                        backend.message_buffer.reset();
                        backend.message_buffer.append(item.message);

                        if (item.has_args)
                        {
                            auto* args_buffer{ backend.arg_buffers_pool.get_args_buffer(item.args_buffer_index) };

                            details::format_args<BufferLimits>(backend.message_buffer, *args_buffer);

                            backend.arg_buffers_pool.release_args_buffer(item.args_buffer_index);
                        }

                        const details::record<Config, BufferLimits> record{
                            backend.message_buffer.c_str(),
                            item.log_level,
                            item.meta, 
                            item.topic_registry 
                        };

                        for (const auto& sink : backend.sink_storage)
                        {
                            if (sink->should_sink(record.log_level))
                            {
                                sink->sink_it(record);
                            }
                        }
                    }
                }
            });
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename Config, typename BufferLimits, typename ConcurrencyModelPolicy, typename... Args>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::log(
        backend<Config, BufferLimits, ConcurrencyModelPolicy>& backend,
        const details::topic_registry<typename Config::topic_t>& topic_registry, std::string_view message, 
        level log_level, const details::source_meta& meta, Args&&... args)
    {
        if constexpr (sizeof...(args) > 0)
        {
            typename asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::
                backend<Config, BufferLimits, ConcurrencyModelPolicy>::queue_item item
            {
                message.data(), 
                log_level, 
                meta, 
                topic_registry
            };

            item.has_args = true;

            const std::uint8_t buf_index{ backend.arg_buffers_pool.acquire_args_buffer() };
            auto* args_buffer{ backend.arg_buffers_pool.get_args_buffer(buf_index) };

            item.args_buffer_index = buf_index;

            std::uint8_t buffer_index{ 0 };
            (details::convert_to_chars((*args_buffer)[buffer_index++],
                BufferLimits::argument, std::forward<Args>(args)), ...);

            backend.queue.enqueue(std::move(item));
        }
        else
        {
            backend.queue.enqueue({ message.data(), log_level, meta, topic_registry });
        }
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename Config, typename BufferLimits, typename ConcurrencyModelPolicy>
    asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::backend<Config, BufferLimits, ConcurrencyModelPolicy>::~backend()
    {
        shutdown.store(true, std::memory_order_relaxed);

        if (worker_thread.joinable())
        {
            worker_thread.join();
        }
    }
}