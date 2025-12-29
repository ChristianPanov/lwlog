#pragma once

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#elif defined(__linux__)
	#include <unistd.h>
	#include <pthread.h>
	#include <sys/syscall.h>
	#include <sched.h>
#elif defined(__APPLE__)
	#include <unistd.h>
	#include <pthread.h>
	#include <mach/mach.h>
	#include <mach/thread_policy.h>
#endif

namespace lwlog::details::os
{
	std::uint64_t get_thread_id();
	std::uint64_t get_process_id();

	struct execution_context
	{
		std::uint64_t thread_id{ get_thread_id() };
		std::uint64_t process_id{ get_process_id() };
	};

	void set_thread_affinity(std::uint64_t affinity_mask);
}

#include "os_impl.h"