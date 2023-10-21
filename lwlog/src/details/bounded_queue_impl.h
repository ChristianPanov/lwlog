#pragma once

#include "bounded_queue.h"

namespace lwlog::details
{
    template<std::size_t Capacity, typename T>
    void bounded_queue<Capacity, T>::enqueue(const T& item)
    {
        const std::size_t current_write_index{ m_write_index.load() };
        const std::size_t next_write_index{ (current_write_index + 1) % Capacity };

        if (next_write_index == m_read_index.load()) {}

        m_storage[current_write_index] = item;
        m_write_index.store(next_write_index);
    }

    template<std::size_t Capacity, typename T>
    T bounded_queue<Capacity, T>::dequeue()
    {
        const std::size_t current_read_index{ m_read_index.load() };
        const std::size_t next_write_index{ (current_read_index + 1) % Capacity };

        if (current_read_index == m_write_index.load()) {}

        m_read_index.store(next_write_index);

        return m_storage[current_read_index];
    }

    template<std::size_t Capacity, typename T>
    bool bounded_queue<Capacity, T>::is_empty() const
    {
        return m_read_index.load() == m_write_index.load();
    }
}