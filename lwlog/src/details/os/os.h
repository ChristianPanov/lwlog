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
	#ifdef LWLOG_USE_THREAD_ID
		using thread_id_t = std::size_t;
	#else
		struct thread_id_t {};
	#endif

	#ifdef LWLOG_USE_PROCESS_ID
		using process_id_t = std::size_t;
	#else
		struct process_id_t {};
	#endif

	struct execution_context
	{
		execution_context()
		{
			#ifdef LWLOG_USE_THREAD_ID
				#if defined(_WIN32)
					thread_id = static_cast<std::size_t>(::GetCurrentThreadId());
				#elif defined(__linux__)
					thread_id = static_cast<std::size_t>(::syscall(SYS_gettid));
				#elif defined(__APPLE__)
					::pthread_threadid_np(NULL, &thread_id);
				#else
					thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
				#endif
			#endif

			#ifdef LWLOG_USE_PROCESS_ID
				#if defined(_WIN32)
					process_id = static_cast<std::size_t>(::GetCurrentProcessId());
				#elif defined(__linux__) || defined(__APPLE__)
					process_id = static_cast<std::size_t>(::getpid());
				#endif
			#endif
		}
		
		thread_id_t thread_id{};
		process_id_t process_id{};
	};

    static bool are_ansi_colors_enabled()
	{
		#ifdef _WIN32
			::HANDLE handle{ ::GetStdHandle(STD_OUTPUT_HANDLE) };
			::DWORD mode{};

			return ::GetConsoleMode(handle, &mode) &&
				(mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING);
		#else
			return true;
		#endif
	}

	static void enable_ansi_colors()
	{
		#ifdef _WIN32
			::HANDLE handle{ ::GetStdHandle(STD_OUTPUT_HANDLE) };
			::DWORD mode{};

			if (handle == INVALID_HANDLE_VALUE) return;
			if (!::GetConsoleMode(handle, &mode)) return;

			mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

			if (!::SetConsoleMode(handle, mode)) return;
		#endif
	}
}