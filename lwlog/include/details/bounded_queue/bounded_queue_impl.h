#pragma once

#include "bounded_queue.h"

namespace lwlog::details
{
    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename... Args>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::enqueue(Args&&... args)
    {
        this->enqueue_impl(ConcurrencyModelPolicy{}, std::forward<Args>(args)...);
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename... Args>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::enqueue_impl(
        [[maybe_unused]] spsc_model_policy, Args&&... args)
    {
        const std::size_t write_index{ m_write_index.load(std::memory_order_relaxed) };

        for (;;)
        {
            if (write_index - m_cached_read_index < Capacity) 
            { 
                break;
            }

            m_cached_read_index = m_read_index.load(std::memory_order_acquire);

            if (write_index - m_cached_read_index < Capacity) 
            { 
                break; 
            }

            if constexpr (OverflowPolicy::block_on_full)
            {
                LWLOG_CPU_PAUSE();
            }
            else
            {
                return;
            }
        }

        m_storage.construct_at(write_index, std::forward<Args>(args)...);
        m_write_index.store(write_index + 1, std::memory_order_release);
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename... Args>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::enqueue_impl(
        [[maybe_unused]] mpsc_model_policy, Args&&... args)
    {
        for (;;)
        {
            while (m_mpsc_lock.test_and_set(std::memory_order_acquire))
            {
                LWLOG_CPU_PAUSE();
            }

            const std::size_t write_index{ m_write_index.load(std::memory_order_relaxed) };

            if (write_index - m_cached_read_index >= Capacity)
            {
                m_cached_read_index = m_read_index.load(std::memory_order_acquire);
            }

            if (write_index - m_cached_read_index < Capacity)
            {
                m_storage.construct_at(write_index, std::forward<Args>(args)...);
                m_write_index.store(write_index + 1, std::memory_order_release);

                m_mpsc_lock.clear(std::memory_order_release);

                return;
            }

            m_mpsc_lock.clear(std::memory_order_release);

            if constexpr (OverflowPolicy::block_on_full)
            {
                LWLOG_CPU_PAUSE();
            }
            else
            {
                return;
            }
        }
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename Fn>
    bool bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::try_consume_one(Fn&& fn)
    {
        const std::size_t read_index{ m_read_index.load(std::memory_order_relaxed) };

        if (m_cached_write_index == read_index)
        {
            m_cached_write_index = m_write_index.load(std::memory_order_acquire);

            if (m_cached_write_index == read_index)
            {
                return false;
            }
        }

        const T& item{ *m_storage.ptr_at(read_index) };

        std::forward<Fn>(fn)(item);

        m_storage.destroy_at(read_index);
        m_read_index.store(read_index + 1, std::memory_order_release);

        return true;
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    bool bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::is_empty() const
    {
        return m_read_index.load(std::memory_order_relaxed) == m_write_index.load(std::memory_order_acquire);
    }
}