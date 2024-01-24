#include "datetime.h"
#pragma once

namespace lwlog::details::os
{
	template<typename LocalTimePolicy>
	inline std::uint8_t handle_timezone(std::uint8_t hour)
	{
		return {};
	}

	template<>
	inline std::uint8_t handle_timezone<enable_local_time>(std::uint8_t hour)
	{
		hour += m_cached_timezone_offset;
		hour = (hour <= 23) ? hour : hour - 24;

		return hour;
	}

	template<typename LocalTimePolicy, typename PreciseUnitsPolicy>
	time_point<LocalTimePolicy, PreciseUnitsPolicy>::time_point()
	{
		time_point_base::hour = handle_timezone<LocalTimePolicy>(time_point_base::hour);
	}

	template<typename LocalTimePolicy>
	time_point<LocalTimePolicy, enable_precise_units>::time_point()
	{
		#if LWLOG_NO_TIME == 0
			#ifdef _WIN32
				::FILETIME now_ft;
				::GetSystemTimePreciseAsFileTime(&now_ft);

				::ULARGE_INTEGER ticks_since_windows_epoch;
				ticks_since_windows_epoch.LowPart = now_ft.dwLowDateTime;
				ticks_since_windows_epoch.HighPart = now_ft.dwHighDateTime;

				const std::uint64_t ticks_since_last_second{ ticks_since_windows_epoch.QuadPart % 10'000'000 };

				m_millisecond = now.wMilliseconds;
				m_microsecond = (ticks_since_last_second / 10) % 1'000'000;
				m_nanosecond = ticks_since_last_second * 100 % 1'000'000'000;
			#else
				const auto nanoseconds_since_unix_epoch{
					std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count() };

				m_millisecond = (nanoseconds_since_unix_epoch / 1'000'000) % 1'000;
				m_microsecond = (nanoseconds_since_unix_epoch / 1'000) % 1'000'000;
				m_nanosecond = nanoseconds_since_unix_epoch % 1'000'000'000;
			#endif
		#endif

		time_point_base::hour = handle_timezone<LocalTimePolicy>(time_point_base::hour);
	}

	template<typename LocalTimePolicy>
	std::uint16_t time_point<LocalTimePolicy, enable_precise_units>::millisecond() const
	{
		return m_millisecond;
	}

	template<typename LocalTimePolicy>
	std::uint32_t time_point<LocalTimePolicy, enable_precise_units>::microsecond() const
	{
		return m_microsecond;
	}

	template<typename LocalTimePolicy>
	std::uint32_t time_point<LocalTimePolicy, enable_precise_units>::nanosecond() const
	{
		return m_nanosecond;
	}
}