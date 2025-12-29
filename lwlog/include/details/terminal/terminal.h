#pragma once

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#endif

namespace lwlog::details::terminal
{
	inline bool are_colors_supported()
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

	inline void enable_colors()
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