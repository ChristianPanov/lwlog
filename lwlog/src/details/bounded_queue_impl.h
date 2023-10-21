#pragma once

#include "policy/overflow_policy.h"

namespace lwlog::details
{
    template<std::size_t Capacity, typename T, typename OverflowPolicy>
    void bounded_queue<Capacity, T, OverflowPolicy>::enqueue(const T& item)
    {
        const std::size_t current_write_index{ m_write_index.load(std::memory_order_relaxed) };
        const std::size_t next_write_index{ (current_write_index + 1) % Capacity };

        while (next_write_index == m_read_index.load(std::memory_order_acquire)) 
            OverflowPolicy::handle_overflow();

        if (!OverflowPolicy::should_discard())
        {
            m_storage[current_write_index] = item;
            m_write_index.store(next_write_index, std::memory_order_release);
        }
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy>
    T bounded_queue<Capacity, T, OverflowPolicy>::dequeue()
    {
        const std::size_t current_read_index{ m_read_index.load(std::memory_order_relaxed) };
        const std::size_t next_write_index{ (current_read_index + 1) % Capacity };

        while (current_read_index == m_write_index.load(std::memory_order_acquire))
            OverflowPolicy::handle_underflow();

        m_read_index.store(next_write_index, std::memory_order_release);

        return m_storage[current_read_index];
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy>
    bool bounded_queue<Capacity, T, OverflowPolicy>::is_empty() const
    {
        return m_read_index.load(std::memory_order_relaxed) 
            == m_write_index.load(std::memory_order_relaxed);
    }
}