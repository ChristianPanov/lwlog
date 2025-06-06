#pragma once

#include <atomic>
#include <vector>
#include <thread>

#include "policy/concurrency_policy.h"

namespace lwlog::details
{
    template<std::size_t Capacity, typename T, 
        typename OverflowPolicy, typename ConcurrencyModelPolicy>
    struct bounded_queue
    {
        static constexpr auto cache_line_size{ 64 };

    public:
        void enqueue(T&& item);
        const T& dequeue();
        bool is_empty() const;

    private:
        void enqueue(T&& item, [[maybe_unused]] spsc_model_policy);
        void enqueue(T&& item, [[maybe_unused]] mpsc_model_policy);

    private:
        T m_storage[Capacity + 1];
        alignas(cache_line_size) std::atomic_size_t m_write_index{};
        alignas(cache_line_size) std::atomic_size_t m_read_index{};
    };
}

#include "bounded_queue_impl.h"