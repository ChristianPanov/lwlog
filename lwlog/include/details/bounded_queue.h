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
        static constexpr auto index_mask{ Capacity - 1 };

    public:
        void enqueue(T&& item);
        T dequeue();
        bool is_empty() const;

    private:
        void enqueue(T&& item, [[maybe_unused]] spsc_model_policy);
        void enqueue(T&& item, [[maybe_unused]] mpsc_model_policy);

    private:
        T m_storage[Capacity];
        alignas(cache_line_size) std::atomic_size_t m_write_index{};
        alignas(cache_line_size) std::atomic_size_t m_read_index{};
        alignas(cache_line_size) std::atomic_flag m_mpsc_lock{ ATOMIC_FLAG_INIT };
    };
}

#include "bounded_queue_impl.h"