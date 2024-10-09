#pragma once

namespace lwlog::details::os
{
	template<typename ThreadIdPolicy>
	static std::uint64_t get_thread_id()
    {
		std::uint64_t thread_id{};

		#if defined(_WIN32)
			thread_id = static_cast<std::uint64_t>(::GetCurrentThreadId());
		#elif defined(__linux__)
			thread_id = static_cast<std::uint64_t>(::syscall(SYS_gettid));
		#elif defined(__APPLE__)
			::pthread_threadid_np(NULL, &thread_id);
		#else
			thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
		#endif

		return thread_id;
	}

	template<typename ProcessIdPolicy>
	static std::uint64_t get_process_id()
	{
		#if defined(_WIN32)
			return static_cast<std::uint64_t>(::GetCurrentProcessId());
		#elif defined(__linux__) || defined(__APPLE__)
			return static_cast<std::uint64_t>(::getpid());
		#endif
	}

	template<>
	static std::uint64_t get_thread_id<disable_thread_id>()
	{ 
		return {}; 
	}

	template<>
	static std::uint64_t get_process_id<disable_process_id>()
	{ 
		return {}; 
	}

	template<typename ThreadIdPolicy, typename ProcessIdPolicy>
	std::uint64_t execution_context<ThreadIdPolicy, ProcessIdPolicy>::thread_id() const
	{ 
		return get_thread_id<ThreadIdPolicy>();
	}

	template<typename ThreadIdPolicy, typename ProcessIdPolicy>
	std::uint64_t execution_context<ThreadIdPolicy, ProcessIdPolicy>::process_id() const
	{ 
		return get_process_id<ProcessIdPolicy>();
	}

	static bool are_ansi_colors_enabled()
	{
		#ifdef _WIN32
			const ::HANDLE handle{ ::GetStdHandle(STD_OUTPUT_HANDLE) };
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
			const ::HANDLE handle{ ::GetStdHandle(STD_OUTPUT_HANDLE) };
			::DWORD mode{};

			if (handle == INVALID_HANDLE_VALUE) return;
			if (!::GetConsoleMode(handle, &mode)) return;

			mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

			if (!::SetConsoleMode(handle, mode)) return;
		#endif
	}
}