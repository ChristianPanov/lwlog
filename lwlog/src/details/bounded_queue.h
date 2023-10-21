#pragma once

#include <atomic>
#include <vector>

#include "policy/concurrency_policy.h"

namespace lwlog::details
{
    template<std::size_t Capacity, typename T, 
        typename OverflowPolicy, typename ConcurrencyModelPolicy>
    struct bounded_queue
    {
    public:
        void enqueue(const T& item);
        T dequeue();
        bool is_empty() const;

    private:
        void enqueue(const T& item, [[maybe_unused]] spsc_model_policy);
        void enqueue(const T& item, [[maybe_unused]] mpsc_model_policy);

    private:
        std::vector<T> m_storage{ Capacity + 1, T{} };
        alignas(64) std::atomic_size_t m_write_index{};
        alignas(64) std::atomic_size_t m_read_index{};
    };
}

#include "bounded_queue_impl.h"