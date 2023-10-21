#include "log_policy.h"
#pragma once

namespace lwlog
{
    template<typename SinkStorage>
    void synchronous_policy::log(backend<SinkStorage>& backend, const details::record& record)
    {
        for (const auto& sink : backend.sink_storage)
        {
            if (sink->should_sink(record.level))
            {
                sink->sink_it(record);
            }
        }
    }

    template<std::size_t Capacity, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename SinkStorage>
    void asynchronous_policy<Capacity, OverflowPolicy, ConcurrencyModelPolicy>::init(backend<SinkStorage>& backend)
    {
        backend.shutdown.store(false, std::memory_order_relaxed);
        backend.worker_thread = std::thread([&backend]() 
            {
                while (true)
                {
                    if (backend.shutdown.load() && backend.queue.is_empty()) break;

                    if (!backend.queue.is_empty())
                    {
                        const details::record record = backend.queue.dequeue();
                        for (const auto& sink : backend.sink_storage)
                        {
                            if (sink->should_sink(record.level))
                            {
                                sink->sink_it(record);
                            }
                        }
                    }
                }
            });
    }

    template<std::size_t Capacity, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename SinkStorage>
    void asynchronous_policy<Capacity, OverflowPolicy, ConcurrencyModelPolicy>::log(backend<SinkStorage>& backend,
        const details::record& record)
    {
        backend.queue.enqueue(record);
    }

    template<std::size_t Capacity, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename SinkStorage>
    asynchronous_policy<Capacity, OverflowPolicy, ConcurrencyModelPolicy>::backend<SinkStorage>::~backend()
    {
        shutdown.store(true, std::memory_order_relaxed);

        if (worker_thread.joinable())
        {
            worker_thread.join();
        }
    }
}