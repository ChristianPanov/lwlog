#pragma once

#include <atomic>
#include <vector>

namespace lwlog::details
{
    template<std::size_t Capacity, typename T, typename OverflowPolicy>
    struct bounded_queue
    {
    public:
        void enqueue(const T& item);
        T dequeue();
        bool is_empty() const;

    private:
        std::vector<T> m_storage{ Capacity + 1, T{} };
        alignas(64) std::atomic<std::size_t> m_write_index{};
        alignas(64) std::atomic<std::size_t> m_read_index{};
    };
}

#include "bounded_queue_impl.h"