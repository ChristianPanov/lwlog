#pragma once

#ifdef _WIN32
#include "windows_lightweight.h"
#else
#include <unistd.h>
#include <sys/syscall.h>
#endif
#include <thread>

namespace lwlog::details::os
{
	static std::size_t thread_id()
	{
		#if defined(_WIN32)
		return static_cast<std::size_t>(::GetCurrentThreadId());
		#elif defined(__linux__)
		return static_cast<std::size_t>(::syscall(__SYS_gettid));
		#elif defined(__APPLE__)
		std::uint64_t tid;
		::pthread_threadid_np(NULL, &tid);
		return tid;
		#else
		return std::hash<std::thread::id>{}(std::this_thread::get_id());
		#endif
	}
}