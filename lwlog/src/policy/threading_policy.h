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

	struct single_threaded_policy
	{
		using mutex_t = null_mutex;
		using lock = std::lock_guard<null_mutex>;
		using concurrency_model_policy = spsc_model_policy;
	};

	struct multi_threaded_policy
	{
		using mutex_t = std::mutex;
		using lock = std::lock_guard<std::mutex>;
		using concurrency_model_policy = mpsc_model_policy;
	};
}
