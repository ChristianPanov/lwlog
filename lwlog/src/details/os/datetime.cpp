#include "datetime.h"

namespace lwlog::details::os
{
	time_point::time_point()
	{
		#ifndef LWLOG_NO_TIME
			#ifdef _WIN32
				::SYSTEMTIME now;
				::GetSystemTime(&now);
				
				year	= now.wYear;
				month	= now.wMonth;
				weekday	= now.wDayOfWeek;
				day		= now.wDay;
				hour	= now.wHour;
				minute	= now.wMinute;
				second	= now.wSecond;

				#ifdef LWLOG_USE_PRECISE_UNITS
					::FILETIME now_ft;
					::GetSystemTimePreciseAsFileTime(&now_ft);

					::ULARGE_INTEGER ticks_since_windows_epoch;
					ticks_since_windows_epoch.LowPart = now_ft.dwLowDateTime;
					ticks_since_windows_epoch.HighPart = now_ft.dwHighDateTime;

					const std::uint64_t ticks_since_last_second{ ticks_since_windows_epoch.QuadPart % 10'000'000 };

					millisecond = now.wMilliseconds;
					microsecond = (ticks_since_last_second / 10) % 1'000'000;
					nanosecond = ticks_since_last_second * 100 % 1'000'000'000;
				#endif
			#else
				const std::chrono::system_clock::time_point now{ std::chrono::system_clock::now() };
				const std::time_t now_time_t{ std::chrono::system_clock::to_time_t(now) };
				const std::tm* details{ std::gmtime(&now_time_t) };

				year	= details->tm_year + 1900;
				month	= details->tm_mon + 1;
				weekday	= details->tm_wday;
				day		= details->tm_mday;
				hour	= details->tm_hour;
				minute	= details->tm_min;
				second	= details->tm_sec;

				#ifdef LWLOG_USE_PRECISE_UNITS
					const auto nanoseconds_since_unix_epoch{ 
						std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count() };

					millisecond = (nanoseconds_since_unix_epoch / 1'000'000) % 1'000;
					microsecond = (nanoseconds_since_unix_epoch / 1'000) % 1'000'000;
					nanosecond = nanoseconds_since_unix_epoch % 1'000'000'000;
				#endif
			#endif
		#endif
	}

	const std::int16_t datetime::m_cached_timezone_offset = []() {
			#ifdef LWLOG_USE_LOCALTIME
				#ifdef _WIN32
					::TIME_ZONE_INFORMATION tz_info;
					::DWORD result{ ::GetTimeZoneInformation(&tz_info) };

					return -tz_info.Bias / 60;
				#else
					const auto offset_epoch{ std::localtime(new std::time_t(0)) };
					return offset_epoch->tm_hour;
				#endif
			#else
				return 0;
			#endif
		}();

	const std::array<const char*, 12> datetime::m_month_name = { "January", "February", "March", "April", "May", 
		"June", "July", "August", "September", "October", "November", "December" };

	const std::array<const char*, 12> datetime::m_month_name_short = { "Jan", "Feb", "Mar", "Apr", "May", 
		"Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };

	const std::array<const char*, 7> datetime::m_weekday_name = { "Monday", "Tuesday", "Wednesday", "Thursday",
		"Friday", "Saturday", "Sunday" };

	const std::array<const char*, 7> datetime::m_weekday_name_short = { "Mon", "Tue", "Wed", "Thu", 
		"Fri", "Sat", "Sun" };

	std::string datetime::get_date(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return std::to_string(now.year) + "-"
				+ ensure_two_digit_format(now.month) + "-"
				+ ensure_two_digit_format(now.day);
		#else
			return {};
		#endif
	}

	std::string datetime::get_date_short(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return ensure_two_digit_format(now.month) + "/"
				+ ensure_two_digit_format(now.day) + "/"
				+ ensure_two_digit_format(now.year % 100);
		#else
			return {};
		#endif
	}

	std::string datetime::get_year(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return std::to_string(now.year);
		#else
			return {};
		#endif
	}

	std::string datetime::get_year_short(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return ensure_two_digit_format(now.year % 100);
		#else
			return {};
		#endif
	}

	std::string datetime::get_month(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return ensure_two_digit_format(now.month);
		#else
			return {};
		#endif
	}

	std::string datetime::get_month_name(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return m_month_name[now.month - 1];
		#else
			return {};
		#endif
	}

	std::string datetime::get_month_name_short(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return m_month_name_short[now.month - 1];
		#else
			return {};
		#endif
	}

	std::string datetime::get_day(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return ensure_two_digit_format(now.day);
		#else
			return {};
		#endif
	}

	std::string datetime::get_weekday_name(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return m_weekday_name[now.weekday - 1];
		#else
			return {};
		#endif
	}

	std::string datetime::get_weekday_name_short(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return m_weekday_name_short[now.weekday - 1];
		#else
			return {};
		#endif
	}

	std::string datetime::get_time(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
            return ensure_two_digit_format(to_local(now.hour)) + ":"
				+ ensure_two_digit_format(now.minute) + ":"
				+ ensure_two_digit_format(now.second);
		#else
			return {};
		#endif
	}

	std::string datetime::get_24_hour_clock(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return ensure_two_digit_format(to_local(now.hour)) + ":"
				+ ensure_two_digit_format(now.minute);
		#else
			return {};
		#endif
	}

	std::string datetime::get_12_hour_clock(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return ensure_two_digit_format(to_12h(to_local(now.hour))) + ":"
				+ ensure_two_digit_format(now.minute) + ":"
				+ ensure_two_digit_format(now.second) + ampm(now.hour);
		#else
			return {};
		#endif
	}

	std::string datetime::get_ampm(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
			return ampm(to_local(now.hour));
		#else
			return {};
		#endif
	}

	std::string datetime::get_hour_24(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
            return ensure_two_digit_format(to_local(now.hour));
		#else
			return {};
		#endif
	}

	std::string datetime::get_hour_12(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
            return ensure_two_digit_format(to_12h(to_local(now.hour)));
		#else
			return {};
		#endif
	}

	std::string datetime::get_minute(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
            return ensure_two_digit_format(now.minute);
		#else
			return {};
		#endif
	}

	std::string datetime::get_second(const time_point& now)
	{
		#ifndef LWLOG_NO_TIME
            return ensure_two_digit_format(now.second);
		#else
			return {};
		#endif
	}

	std::string datetime::get_millisecond(const time_point& now)
	{
		#if !defined(LWLOG_NO_TIME) && defined(LWLOG_USE_PRECISE_UNITS)
            return std::to_string(now.millisecond);
		#else
			return {};
		#endif
	}

	std::string datetime::get_microsecond(const time_point& now)
	{
		#if !defined(LWLOG_NO_TIME) && defined(LWLOG_USE_PRECISE_UNITS)
            return std::to_string(now.microsecond);
		#else
			return {};
		#endif
	}

	std::string datetime::get_nanosecond(const time_point& now)
	{
		#if !defined(LWLOG_NO_TIME) && defined(LWLOG_USE_PRECISE_UNITS)
            return std::to_string(now.nanosecond);
		#else
			return {};
		#endif
	}

	const char* datetime::ampm(std::uint16_t hour)
	{
		return hour >= 12 ? "pm" : "am";
	}

	std::uint16_t datetime::to_local(std::uint16_t hour)
	{
		const std::uint16_t local = hour + m_cached_timezone_offset;
		return local <= 23 ? local : local - 24;
	}

	std::uint16_t datetime::to_12h(std::uint16_t hour)
	{
		return hour > 12 ? hour - 12 : hour;
	}

	std::string datetime::ensure_two_digit_format(std::uint16_t digit)
	{
		return (digit <= 9 ? "0" : "") + std::to_string(digit);
	}
}