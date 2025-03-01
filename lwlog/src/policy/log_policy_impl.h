#pragma once

#include "log_policy.h"

namespace lwlog
{
    template<typename Config, typename BufferLimits, typename ConcurrencyModelPolicy, typename... Args>
    void synchronous_policy::log(backend<Config, BufferLimits, ConcurrencyModelPolicy>& backend, 
        const char* const message, level log_level, const details::source_meta& meta, Args&&... args)
    {
        backend.message_buffer.reset();
        backend.message_buffer.append(message);

        if constexpr (sizeof...(args) > 0)
        {
            std::uint8_t buffer_index{ 0 };
            (details::convert_to_chars(backend.args_buffers[buffer_index++],
                BufferLimits::argument, std::forward<Args>(args)), ...);

            details::format_args<BufferLimits>(backend.message_buffer, backend.args_buffers);
        }

        for (const auto& sink : backend.sink_storage)
        {
            if (sink->should_sink(log_level))
            {
                sink->sink_it({ backend.message_buffer.c_str(), log_level, meta, backend.topics });
            }
        }
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename Config, typename BufferLimits, typename ConcurrencyModelPolicy>
    struct asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::backend<
        Config, BufferLimits, ConcurrencyModelPolicy>::queue_item
    {
        bool has_args{ false };
        std::uint8_t args_buffer_index{ 0 };

        const char* message;
        level log_level;
        details::source_meta meta;
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
                        const auto& item{ backend.queue.dequeue() };

                        backend.message_buffer.reset();
                        backend.message_buffer.append(item.message);

                        if (item.has_args)
                        {
                            const auto& args_buffer{ backend.arg_buffers_pool.get_args_buffer(item.args_buffer_index) };

                            details::format_args<BufferLimits>(backend.message_buffer, args_buffer);

                            backend.arg_buffers_pool.release_args_buffer(item.args_buffer_index);
                        }

                        for (const auto& sink : backend.sink_storage)
                        {
                            if (sink->should_sink(item.log_level))
                            {
                                sink->sink_it({ backend.message_buffer.c_str(), item.log_level, 
                                    item.meta, backend.topics });
                            }
                        }
                    }
                }
            });
    }

    template<typename OverflowPolicy, std::size_t Capacity, std::uint64_t ThreadAffinity>
    template<typename Config, typename BufferLimits, typename ConcurrencyModelPolicy, typename... Args>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::log(
        backend<Config, BufferLimits, ConcurrencyModelPolicy>& backend, const char* const message,
        level log_level, const details::source_meta& meta, Args&&... args)
    {
        if constexpr (sizeof...(args) == 0)
        {
            backend.queue.enqueue({ false, 0, message, log_level, meta });
        }
        else
        {
            const std::uint8_t buff_index{ backend.arg_buffers_pool.acquire_args_buffer() };
            auto& args_buffer{ backend.arg_buffers_pool.get_args_buffer(buff_index) };

            std::uint8_t buffer_index{ 0 };
            (details::convert_to_chars(args_buffer[buffer_index++],
                BufferLimits::argument, std::forward<Args>(args)), ...);

            backend.queue.enqueue({ true, buff_index, message, log_level, meta });
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