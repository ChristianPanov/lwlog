#pragma once

namespace lwlog
{
    template<typename Config, typename ConcurrencyModelPolicy>
    void synchronous_policy::log(backend<Config, ConcurrencyModelPolicy>& backend, 
        const details::topic_registry<typename Config::topic_t>& topic_registry, std::string_view message, 
        level log_level, const details::source_meta& meta, details::format_args_list args)
    {
        const auto formatted_message{ details::format_args(message, args) };
        const details::record<Config> record{ formatted_message, log_level, meta, topic_registry };

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
        details::format_args_list                           args;
        details::topic_registry<typename Config::topic_t>   topic_registry;
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
                        const auto& item{ backend.queue.dequeue() };
                        const auto formatted_message{ details::format_args(item.message, item.args) };

                        const details::record<Config> record{ 
                            formatted_message, 
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
    template<typename Config, typename ConcurrencyModelPolicy>
    void asynchronous_policy<OverflowPolicy, Capacity, ThreadAffinity>::log(
        backend<Config, ConcurrencyModelPolicy>& backend,
        const details::topic_registry<typename Config::topic_t>& topic_registry, std::string_view message, 
        level log_level, const details::source_meta& meta, details::format_args_list args)
    {
        backend.queue.enqueue({ message, log_level, meta, args, topic_registry });
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
