#pragma once

#include <mutex>

#include "concurrency_policy.h"

namespace lwlog
{
	struct null_mutex 
	{
		static void lock() {}
		static void unlock() {}
	};

	template<typename T>
	class null_atomic
	{
	public:
        null_atomic() = default;
		null_atomic(T value) 
			: m_value{ value }
		{}

        T load(std::memory_order = std::memory_order_relaxed) const
        {
            return m_value;
        }

        void store(T value, std::memory_order = std::memory_order_relaxed)
        {
            m_value = value;
        }

	private:
        T m_value{};
	};

	struct single_threaded_policy
	{
		template<typename T>
		using atomic_t = null_atomic<T>;
		using mutex_t = null_mutex;
		using lock_t = std::lock_guard<null_mutex>;
		using concurrency_model_policy = spsc_model_policy;
	};

	struct multi_threaded_policy
	{
		template<typename T>
		using atomic_t = std::atomic<T>;
		using mutex_t = std::mutex;
		using lock_t = std::lock_guard<std::mutex>;
		using concurrency_model_policy = mpsc_model_policy;
	};
}