#pragma once

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#else
	#include <chrono>
#endif

#include "datetime_utility.h"
#include "details/memory_buffer.h"

namespace lwlog::details::os
{
	class time_point
	{
	public:
		time_point()
		{
		#ifdef _WIN32
			::SYSTEMTIME m_now;

			::GetSystemTime(&m_now);

			year 	= m_now.wYear;
			month 	= m_now.wMonth;
			weekday = m_now.wDayOfWeek;
			day 	= m_now.wDay;
			minute 	= m_now.wMinute;
			second 	= m_now.wSecond;

			hour = datetime::handle_timezone(static_cast<std::uint8_t>(m_now.wHour));

			::FILETIME now_ft;
			::GetSystemTimePreciseAsFileTime(&now_ft);

			::ULARGE_INTEGER ticks_since_windows_epoch;
			ticks_since_windows_epoch.LowPart = now_ft.dwLowDateTime;
			ticks_since_windows_epoch.HighPart = now_ft.dwHighDateTime;

			const std::uint64_t ticks_since_last_second{ ticks_since_windows_epoch.QuadPart % 10'000'000 };

			millisecond = m_now.wMilliseconds;
			microsecond = (ticks_since_last_second / 10) % 1'000'000;
			nanosecond = (ticks_since_last_second * 100) % 1'000'000'000;
		#else
			std::chrono::system_clock::time_point m_now;

		    m_now = std::chrono::system_clock::now();
			const std::time_t now_time_t{ std::chrono::system_clock::to_time_t(m_now) };

			std::tm details;
			gmtime_r(&now_time_t, &details);

			year 	= static_cast<std::uint16_t>(details.tm_year) + 1900;
			month 	= static_cast<std::uint8_t>(details.tm_mon) + 1;
			weekday = static_cast<std::uint8_t>(details.tm_wday);
			day 	= static_cast<std::uint8_t>(details.tm_mday);
			minute 	= static_cast<std::uint8_t>(details.tm_min);
			second 	= static_cast<std::uint8_t>(details.tm_sec);

			hour = datetime::handle_timezone<LocalTimePolicy>(static_cast<std::uint8_t>(details.tm_hour));

			const auto nanoseconds_since_unix_epoch{ 
				std::chrono::duration_cast<std::chrono::nanoseconds>(m_now.time_since_epoch()).count() };

			millisecond = (nanoseconds_since_unix_epoch / 1'000'000) % 1'000;
			microsecond = (nanoseconds_since_unix_epoch / 1'000) % 1'000'000;
			nanosecond = nanoseconds_since_unix_epoch % 1'000'000'000;
		#endif
	}

	public:
        std::uint16_t year;
        std::uint8_t month;
        std::uint8_t weekday;
        std::uint8_t day;
        std::uint8_t hour;
        std::uint8_t minute;
        std::uint8_t second;
        std::uint16_t millisecond;
        std::uint32_t microsecond;
        std::uint32_t nanosecond;
	};
}