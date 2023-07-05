#pragma once

#include <mutex>

namespace lwlog
{
	struct null_mutex 
	{
		static void lock() {}
		static void unlock() {}
	};

	template<typename Mutex>
	struct threading_policy
	{
		using mutex_t = Mutex;
		using lock = std::lock_guard<Mutex>;
	};
}