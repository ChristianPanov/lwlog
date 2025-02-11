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
	template<typename ThreadIdPolicy>
	static std::uint64_t get_thread_id();

	template<typename ProcessIdPolicy>
	static std::uint64_t get_process_id();

	struct execution_context_base
	{
		virtual ~execution_context_base() = default;

		virtual std::uint64_t thread_id() const = 0;
		virtual std::uint64_t process_id() const = 0;
	};

	template<typename ThreadIdPolicy, typename ProcessIdPolicy>
	struct execution_context : public execution_context_base
	{
		std::uint64_t thread_id() const override;
		std::uint64_t process_id() const override;
	};

	static void set_thread_affinity(std::uint64_t affinity_mask);

	static bool are_ansi_colors_enabled();
	static void enable_ansi_colors();
}

#include "os_impl.h"
