#pragma once

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#elif defined(__linux__) || defined(__APPLE__)
	#include <unistd.h>
	#include <sys/syscall.h>
#else
	#include <thread>
#endif

namespace lwlog::details::os
{
	template<typename ThreadIdPolicy>
	static std::size_t get_thread_id();

	template<typename ProcessIdPolicy>
	static std::size_t get_process_id();

	struct execution_context_base
	{
		virtual std::size_t thread_id() const = 0;
		virtual std::size_t process_id() const = 0;
	};

	template<typename ThreadIdPolicy, typename ProcessIdPolicy>
	struct execution_context : public execution_context_base 
	{
		std::size_t thread_id() const override;
		std::size_t process_id() const override;
	};

	static bool are_ansi_colors_enabled();
	static void enable_ansi_colors();
}

#include "os_impl.h"