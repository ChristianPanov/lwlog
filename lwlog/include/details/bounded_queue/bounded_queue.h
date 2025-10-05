#pragma once

#include <atomic>

#include "bounded_queue_storage.h"
#include "policy/concurrency_policy.h"

namespace lwlog::details
{
    template<std::size_t Capacity, typename T, 
        typename OverflowPolicy, typename ConcurrencyModelPolicy>
    struct bounded_queue
    {
        static_assert(Capacity && (Capacity & (Capacity - 1)) == 0, "Capacity must be a power of 2");

        using overflow_adapter = overflow_adapter<bounded_queue<Capacity, T,
            OverflowPolicy, ConcurrencyModelPolicy>, OverflowPolicy>;

        friend overflow_adapter;

        static constexpr auto cache_line_size{ 64 };

    public:
        template<typename... Args>
        void enqueue(Args&&... args);

        T dequeue();
        bool is_empty() const;

    private:
        template<typename... Args> void enqueue_slow([[maybe_unused]] spsc_model_policy, Args&&... args);
        template<typename... Args> void enqueue_slow([[maybe_unused]] mpsc_model_policy, Args&&... args);

        template<typename... Args> bool try_enqueue([[maybe_unused]] spsc_model_policy, Args&&... args);
        template<typename... Args> bool try_enqueue([[maybe_unused]] mpsc_model_policy, Args&&... args);

    private:
        void advance_read_index();

    private:
        bounded_queue_storage<T, Capacity> m_storage;

        alignas(cache_line_size) std::atomic_size_t m_write_index{};
        alignas(cache_line_size) std::atomic_size_t m_read_index{};
        alignas(cache_line_size) std::atomic_flag m_mpsc_lock{ ATOMIC_FLAG_INIT };
    };
}

#include "bounded_queue_impl.h"