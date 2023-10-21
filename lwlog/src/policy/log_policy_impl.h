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

    template<std::size_t Capacity, typename OverflowPolicy>
    template<typename SinkStorage>
    void asynchronous_policy<Capacity, OverflowPolicy>::init(backend<SinkStorage>& backend)
    {
        backend.shutdown.store(false);
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

    template<std::size_t Capacity, typename OverflowPolicy>
    template<typename SinkStorage>
    void asynchronous_policy<Capacity, OverflowPolicy>::log(backend<SinkStorage>& backend, 
        const details::record& record)
    {
        backend.queue.enqueue(record);
    }

    template<std::size_t Capacity, typename OverflowPolicy>
    template<typename SinkStorage>
    asynchronous_policy<Capacity, OverflowPolicy>::backend<SinkStorage>::~backend()
    {
        shutdown.store(true);

        if(worker_thread.joinable())
            worker_thread.join();
    }
}