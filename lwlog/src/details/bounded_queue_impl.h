#pragma once

#include "policy/overflow_policy.h"

namespace lwlog::details
{
    template<std::size_t Capacity, typename T, typename OverflowPolicy>
    void bounded_queue<Capacity, T, OverflowPolicy>::enqueue(const T& item)
    {
        const std::size_t current_write_index{ m_write_index.load() };
        const std::size_t next_write_index{ (current_write_index + 1) % Capacity };

        while (next_write_index == m_read_index.load()) 
            OverflowPolicy::handle_overflow();

        if (!OverflowPolicy::should_discard())
        {
            m_storage[current_write_index] = item;
            m_write_index.store(next_write_index);
        }
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy>
    T bounded_queue<Capacity, T, OverflowPolicy>::dequeue()
    {
        const std::size_t current_read_index{ m_read_index.load() };
        const std::size_t next_write_index{ (current_read_index + 1) % Capacity };

        while (current_read_index == m_write_index.load())
            OverflowPolicy::handle_underflow();

        m_read_index.store(next_write_index);

        return m_storage[current_read_index];
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy>
    bool bounded_queue<Capacity, T, OverflowPolicy>::is_empty() const
    {
        return m_read_index.load() == m_write_index.load();
    }
}