#pragma once

#include "bounded_queue.h"

namespace lwlog::details
{
    template<std::size_t Capacity, typename T,
        typename OverflowPolicy, typename ConcurrencyModelPolicy>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::enqueue(const T& item)
    {
        this->enqueue(item, ConcurrencyModelPolicy{});
    }

    template<std::size_t Capacity, typename T,
        typename OverflowPolicy, typename ConcurrencyModelPolicy>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::enqueue(const T& item,
        [[maybe_unused]] spsc_model_policy)
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

    template<std::size_t Capacity, typename T,
        typename OverflowPolicy, typename ConcurrencyModelPolicy>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::enqueue(const T& item,
        [[maybe_unused]] mpsc_model_policy)
    {
        std::size_t current_write_index;
        std::size_t next_write_index;

        do
        {
            current_write_index = m_write_index.load(std::memory_order_relaxed);
            next_write_index = (current_write_index + 1) % Capacity;

            while (next_write_index == m_read_index.load(std::memory_order_acquire))
                OverflowPolicy::handle_overflow();

        } while (!m_write_index.compare_exchange_weak(current_write_index, next_write_index, 
            std::memory_order_release, 
            std::memory_order_relaxed));

        if (!OverflowPolicy::should_discard())
            m_storage[current_write_index] = item;
    }

    template<std::size_t Capacity, typename T,
        typename OverflowPolicy, typename ConcurrencyModelPolicy>
    T bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::dequeue()
    {
        const std::size_t current_read_index{ m_read_index.load(std::memory_order_relaxed) };
        const std::size_t next_write_index{ (current_read_index + 1) % Capacity };

        while (current_read_index == m_write_index.load(std::memory_order_acquire))
            OverflowPolicy::handle_underflow();

        m_read_index.store(next_write_index, std::memory_order_release);

        return m_storage[current_read_index];
    }

    template<std::size_t Capacity, typename T,
        typename OverflowPolicy, typename ConcurrencyModelPolicy>
    bool bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::is_empty() const
    {
        return m_read_index.load(std::memory_order_relaxed) 
            == m_write_index.load(std::memory_order_relaxed);
    }
}