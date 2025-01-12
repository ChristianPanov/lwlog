#pragma once

#include "details/memory_buffer.h"

#include <charconv>
#include <iostream>

namespace lwlog
{
    template<typename Config, typename ConcurrencyModelPolicy, typename... Args>
    void synchronous_policy::log(backend<Config, ConcurrencyModelPolicy>& backend, 
        const details::topic_registry<typename Config::topic_t>& topic_registry, std::string_view message, 
        level log_level, const details::source_meta& meta, Args&&... args)
    {
        char args_buffers[10][24]{};
        if (sizeof...(args) > 0)
        {
            std::uint8_t buffer_index{ 0 };
            (details::convert_to_chars(args_buffers[buffer_index++], 24, std::forward<Args>(args)), ...);
        }

        details::record<Config> record{ message, log_level, meta, topic_registry };
        details::format_args(record.message_buffer, args_buffers);

        for (const auto& sink : backend.sink_storage)
        {
            if (sink->should_sink(record.log_level))
            {
                sink->sink_it(record);
            }
        }
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename Config, typename ConcurrencyModelPolicy>
    struct asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::backend<
        Config, ConcurrencyModelPolicy>::queue_item
    {
        std::string_view			                        message;
        level						                        log_level;
        details::source_meta		                        meta;
        details::topic_registry<typename Config::topic_t>   topic_registry;

        std::function<void(char(&args_buffers)[10][24])>    lazy_convert_to_chars;
        char						                        args_buffers[10][24]{};
    };

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename Config, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::init(
        backend<Config, ConcurrencyModelPolicy>& backend)
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

                        details::record<Config> record{ 
                            item.message, 
                            item.log_level,
                            item.meta, 
                            item.topic_registry 
                        };

                        if (item.lazy_convert_to_chars)
                        {
                            item.lazy_convert_to_chars(item.args_buffers);
                            details::format_args(record.message_buffer, item.args_buffers);
                        }

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
    template<typename Config, typename ConcurrencyModelPolicy, typename... Args>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::log(
        backend<Config, ConcurrencyModelPolicy>& backend,
        const details::topic_registry<typename Config::topic_t>& topic_registry, std::string_view message, 
        level log_level, const details::source_meta& meta, Args&&... args)
    {
        if constexpr(sizeof...(args) == 0)
        {
            backend.queue.enqueue({ message, log_level, meta, topic_registry });
        }
        else
        {
            backend.queue.enqueue({ message, log_level, meta, topic_registry, 
                [args...](char(&args_buffers)[10][24])
                { 
                    std::uint8_t buffer_index{ 0 };
                    (details::convert_to_chars(args_buffers[buffer_index++], 24, args), ...);
                } 
            });
        }
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename Config, typename ConcurrencyModelPolicy>
    asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::backend<Config, ConcurrencyModelPolicy>::~backend()
    {
        shutdown.store(true, std::memory_order_relaxed);

        if (worker_thread.joinable())
        {
            worker_thread.join();
        }
    }
}