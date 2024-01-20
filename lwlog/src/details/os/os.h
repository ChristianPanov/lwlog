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
	static std::size_t get_thread_id()
	{
		std::size_t thread_id{};

		#if defined(_WIN32)
			thread_id = static_cast<std::size_t>(::GetCurrentThreadId());
		#elif defined(__linux__)
			thread_id = static_cast<std::size_t>(::syscall(SYS_gettid));
		#elif defined(__APPLE__)
			::pthread_threadid_np(NULL, &thread_id);
		#else
			thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
		#endif

		return thread_id;
	}

	static std::size_t get_process_id()
	{
		#if defined(_WIN32)
			return static_cast<std::size_t>(::GetCurrentProcessId());
		#elif defined(__linux__) || defined(__APPLE__)
			return static_cast<std::size_t>(::getpid());
		#endif
	}

	struct execution_context_base
	{
		virtual std::size_t thread_id() const = 0;
		virtual std::size_t process_id() const = 0;
	};

	template<typename ThreadIdPolicy, typename ProcessIdPolicy>
	struct execution_context : public execution_context_base {};

	template<>
	struct execution_context<disable_thread_id, disable_process_id>
		: public execution_context_base
	{
		std::size_t thread_id()		const override { return 0; }
		std::size_t process_id()	const override { return 0; }
	};

	template<>
	struct execution_context<enable_thread_id, disable_process_id>
		: public execution_context_base
	{
		std::size_t thread_id()		const override { return get_thread_id(); }
		std::size_t process_id()	const override { return 0; }
	};

	template<>
	struct execution_context<disable_thread_id, enable_process_id>
		: public execution_context_base
	{
		std::size_t thread_id()		const override { return 0; }
		std::size_t process_id()	const override { return get_process_id(); }
	};

	template<>
	struct execution_context<enable_thread_id, enable_process_id>
		: public execution_context_base
	{
		std::size_t thread_id()		const override { return get_thread_id(); }
		std::size_t process_id()	const override { return get_process_id(); }
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