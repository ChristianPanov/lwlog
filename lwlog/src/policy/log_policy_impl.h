#include "log_policy.h"

namespace lwlog
{
    template<typename ConcurrencyModelPolicy>
    void synchronous_policy::log(backend<ConcurrencyModelPolicy>& backend, const details::record& record)
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
    template<typename ConcurrencyModelPolicy>
    void asynchronous_policy<Capacity, OverflowPolicy>::init(backend<ConcurrencyModelPolicy>& backend)
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

    template<std::size_t Capacity, typename OverflowPolicy>
    template<typename ConcurrencyModelPolicy>
    void asynchronous_policy<Capacity, OverflowPolicy>::log(backend<ConcurrencyModelPolicy>& backend,
        const details::record& record)
    {
        backend.queue.enqueue(record);
    }

    template<std::size_t Capacity, typename OverflowPolicy>
    template<typename ConcurrencyModelPolicy>
    asynchronous_policy<Capacity, OverflowPolicy>::backend<ConcurrencyModelPolicy>::~backend()
    {
        shutdown.store(true, std::memory_order_relaxed);

        if (worker_thread.joinable())
        {
            worker_thread.join();
        }
    }
}