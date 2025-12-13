#pragma once

namespace lwlog::details
{
    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename... Args>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::enqueue(Args&&... args)
    {
        const bool can_enqueue{ this->try_enqueue(ConcurrencyModelPolicy{}, std::forward<Args>(args)...) };

        if (!can_enqueue)
        {
            this->enqueue_slow(ConcurrencyModelPolicy{}, std::forward<Args>(args)...);
        }
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename... Args>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::enqueue_slow(
        [[maybe_unused]] spsc_model_policy, Args&&... args)
    {
        const std::size_t write_index{ m_write_index.load(std::memory_order_relaxed) };

        for (;;)
        {
            const std::size_t read_index{ m_read_index.load(std::memory_order_relaxed) };

            if ((write_index - read_index) < Capacity)
            {
                m_storage.construct_at(write_index, std::forward<Args>(args)...);
                m_write_index.store(write_index + 1, std::memory_order_release);

                return;
            }

            switch (overflow_adapter::handle_full(*this))
            {
            case overflow_action::discard_new:      return;
            case overflow_action::overwrite_last:   continue;
            case overflow_action::wait:             continue;
            }
        }
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename... Args>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::enqueue_slow(
        [[maybe_unused]] mpsc_model_policy, Args&&... args)
    {
        for (;;)
        {
            while (m_mpsc_lock.test_and_set(std::memory_order_acquire))
            {
                LWLOG_CPU_PAUSE();
            }

            const std::size_t write_index{ m_write_index.load(std::memory_order_relaxed) };
            const std::size_t read_index{ m_read_index.load(std::memory_order_relaxed) };

            if ((write_index - read_index) < Capacity)
            {
                m_storage.construct_at(write_index, std::forward<Args>(args)...);
                m_write_index.store(write_index + 1, std::memory_order_release);

                m_mpsc_lock.clear(std::memory_order_release);

                return;
            }

            m_mpsc_lock.clear(std::memory_order_release);

            switch (overflow_adapter::handle_full(*this))
            {
            case overflow_action::discard_new:      return;
            case overflow_action::overwrite_last:   continue;
            case overflow_action::wait:             continue;
            }
        }
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename... Args>
    bool bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::try_enqueue(spsc_model_policy, Args&&... args)
    {
        const std::size_t write_index{ m_write_index.load(std::memory_order_relaxed) };
        const std::size_t read_index{ m_read_index.load(std::memory_order_relaxed) };

        if ((write_index - read_index) < Capacity)
        {
            m_storage.construct_at(write_index, std::forward<Args>(args)...);
            m_write_index.store(write_index + 1, std::memory_order_release);

            return true;
        }

        return false;
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    template<typename... Args>
    bool bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::try_enqueue(mpsc_model_policy, Args&&... args)
    {
        if (m_mpsc_lock.test_and_set(std::memory_order_acquire))
        {
            return false;
        }

        const std::size_t write_index{ m_write_index.load(std::memory_order_relaxed) };
        const std::size_t read_index{ m_read_index.load(std::memory_order_relaxed) };

        if ((write_index - read_index) < Capacity)
        {
            m_storage.construct_at(write_index, std::forward<Args>(args)...);
            m_write_index.store(write_index + 1, std::memory_order_release);

            m_mpsc_lock.clear(std::memory_order_release);
            return true;
        }

        m_mpsc_lock.clear(std::memory_order_release);
        return false;
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    T bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::dequeue()
    {
        for (;;)
        {
            const std::size_t write_index{ m_write_index.load(std::memory_order_acquire) };
            const std::size_t read_index{ m_read_index.load(std::memory_order_relaxed) };

            if ((write_index - read_index) != 0)
            {
                T out{ m_storage.extract_at(read_index) };
                m_read_index.fetch_add(1, std::memory_order_release);

                return out;
            }

            overflow_adapter::handle_empty();
        }
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    bool bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::is_empty() const
    {
        return m_read_index.load(std::memory_order_relaxed) 
            == m_write_index.load(std::memory_order_relaxed);
    }

    template<std::size_t Capacity, typename T, typename OverflowPolicy, typename ConcurrencyModelPolicy>
    void bounded_queue<Capacity, T, OverflowPolicy, ConcurrencyModelPolicy>::advance_read_index()
    {
        m_read_index.fetch_add(1, std::memory_order_acq_rel);
    }
}