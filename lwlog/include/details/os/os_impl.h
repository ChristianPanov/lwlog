#pragma once

namespace lwlog::details::os
{
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

	static std::uint64_t get_process_id()
	{		
		#if defined(_WIN32)
				return static_cast<std::uint64_t>(::GetCurrentProcessId());
		#elif defined(__linux__) || defined(__APPLE__)
				return static_cast<std::uint64_t>(::getpid());
		#endif
	}

	static void set_thread_affinity(std::uint64_t affinity_mask)
	{
		#ifdef _WIN32
			const ::DWORD_PTR mask = static_cast<::DWORD_PTR>(affinity_mask);
			if (::SetThreadAffinityMask(::GetCurrentThread(), mask) == 0) return;
		#elif defined(__linux__)
			::cpu_set_t cpuset;
			CPU_ZERO(&cpuset);

			const std::uint8_t num_cores{ static_cast<std::uint8_t>(::sysconf(_SC_NPROCESSORS_ONLN)) };
			for (std::uint8_t i = 0; i < num_cores; ++i)
			{
				if (affinity_mask & (1ULL << i)) 
				{
					CPU_SET(i, &cpuset);
				}
			}

			if (::pthread_setaffinity_np(::pthread_self(),
				sizeof(::cpu_set_t), &cpuset) != 0) return;
		#elif defined(__APPLE__)
			::thread_affinity_policy_data_t policy{ 
				static_cast<::integer_t>(affinity_mask) 
			};

			::thread_port_t mach_thread = ::pthread_mach_thread_np(::pthread_self());

			if(::thread_policy_set(mach_thread, 
				THREAD_AFFINITY_POLICY, reinterpret_cast<thread_policy_t>(&policy),
				THREAD_AFFINITY_POLICY_COUNT) != KERN_SUCCESS) return;
		#endif
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