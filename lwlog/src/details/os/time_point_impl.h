#pragma once

namespace lwlog::details::os
{
	inline time_point_base::time_point_base()
	{
		#ifdef _WIN32
			::GetSystemTime(&m_now);
			
			year	= m_now.wYear;
			month	= m_now.wMonth;
			weekday	= m_now.wDayOfWeek;
			day		= m_now.wDay;
			hour	= m_now.wHour;
			minute	= m_now.wMinute;
			second	= m_now.wSecond;
		#else
		    m_now = std::chrono::system_clock::now();
			const std::time_t now_time_t{ std::chrono::system_clock::to_time_t(m_now) };
			const std::tm* details{ std::gmtime(&now_time_t) };

			year	= details->tm_year + 1900;
			month	= details->tm_mon + 1;
			weekday	= details->tm_wday;
			day		= details->tm_mday;
			hour	= details->tm_hour;
			minute	= details->tm_min;
			second	= details->tm_sec;
		#endif
	}

	inline std::uint16_t time_point_base::millisecond() const
	{
		return {};
	}

	inline std::uint32_t time_point_base::microsecond() const
	{
		return {};
	}

	inline std::uint32_t time_point_base::nanosecond()	const
	{
		return {};
	}

	inline std::string time_point_base::ampm() const
	{
		return time_point_base::hour >= 12 ? "pm" : "am";
	}

	inline std::string time_point_base::to_string(std::string_view unit) const
	{
		return unit.data();
	}

	inline std::string time_point_base::to_string(std::uint32_t unit) const
	{
		return datetime::ensure_two_digit_format(unit);
	}

	inline std::string time_point_base::build_timestamp(std::uint32_t first_unit,
		std::uint32_t second_unit, char delimeter) const
	{
		return datetime::ensure_two_digit_format(first_unit) + delimeter
			+ datetime::ensure_two_digit_format(second_unit);
	}

	inline std::string time_point_base::build_timestamp(std::uint32_t first_unit,
		std::uint32_t second_unit, std::uint32_t third_unit, char delimeter) const
	{
		return datetime::ensure_two_digit_format(first_unit) + delimeter
			+ datetime::ensure_two_digit_format(second_unit) + delimeter
			+ datetime::ensure_two_digit_format(third_unit);
	}

	template<typename LocalTimePolicy, typename PreciseUnitsPolicy>
	std::string time_point<disable_time, LocalTimePolicy, PreciseUnitsPolicy>::ampm() const
	{
		return {};
	}

	template<typename LocalTimePolicy, typename PreciseUnitsPolicy>
	std::string time_point<disable_time, LocalTimePolicy, PreciseUnitsPolicy>::to_string(std::string_view unit) const
	{
		return {};
	}

	template<typename LocalTimePolicy, typename PreciseUnitsPolicy>
	std::string time_point<disable_time, LocalTimePolicy, PreciseUnitsPolicy>::to_string(std::uint32_t unit) const
	{
		return {};
	}

	template<typename LocalTimePolicy, typename PreciseUnitsPolicy>
	std::string time_point<disable_time, LocalTimePolicy, PreciseUnitsPolicy>::build_timestamp(
		std::uint32_t first_unit, std::uint32_t second_unit, char delimeter) const
	{
		return {};
	}

	template<typename LocalTimePolicy, typename PreciseUnitsPolicy>
	std::string time_point<disable_time, LocalTimePolicy, PreciseUnitsPolicy>::build_timestamp(
		std::uint32_t first_unit, std::uint32_t second_unit, std::uint32_t third_unit, char delimeter) const
	{
		return {};
	}

	template<typename TimePolicy, typename LocalTimePolicy, typename PreciseUnitsPolicy>
	time_point<TimePolicy, LocalTimePolicy, PreciseUnitsPolicy>::time_point()
	{
		time_point_base::hour = datetime::handle_timezone<LocalTimePolicy>(time_point_base::hour);
	}

	template<typename LocalTimePolicy>
	time_point<enable_time, LocalTimePolicy, enable_precise_units>::time_point()
	{
		#ifdef _WIN32
			::FILETIME now_ft;
			::GetSystemTimePreciseAsFileTime(&now_ft);

			::ULARGE_INTEGER ticks_since_windows_epoch;
			ticks_since_windows_epoch.LowPart = now_ft.dwLowDateTime;
			ticks_since_windows_epoch.HighPart = now_ft.dwHighDateTime;

			const std::uint64_t ticks_since_last_second{ ticks_since_windows_epoch.QuadPart % 10'000'000 };

			m_millisecond = m_now.wMilliseconds;
			m_microsecond = (ticks_since_last_second / 10) % 1'000'000;
			m_nanosecond = ticks_since_last_second * 100 % 1'000'000'000;
		#else
			const auto nanoseconds_since_unix_epoch{
				std::chrono::duration_cast<std::chrono::nanoseconds>(m_now.time_since_epoch()).count() };

			m_millisecond = (nanoseconds_since_unix_epoch / 1'000'000) % 1'000;
			m_microsecond = (nanoseconds_since_unix_epoch / 1'000) % 1'000'000;
			m_nanosecond = nanoseconds_since_unix_epoch % 1'000'000'000;
		#endif

		time_point_base::hour = datetime::handle_timezone<LocalTimePolicy>(time_point_base::hour);
	}

	template<typename LocalTimePolicy>
	std::uint16_t time_point<enable_time, LocalTimePolicy, enable_precise_units>::millisecond() const
	{
		return m_millisecond;
	}

	template<typename LocalTimePolicy>
	std::uint32_t time_point<enable_time, LocalTimePolicy, enable_precise_units>::microsecond() const
	{
		return m_microsecond;
	}

	template<typename LocalTimePolicy>
	std::uint32_t time_point<enable_time, LocalTimePolicy, enable_precise_units>::nanosecond() const
	{
		return m_nanosecond;
	}
}