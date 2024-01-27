#pragma once

#include <string>
#include <array>
#include <ctime>
#include <vector>

#include "tweakme.h"

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#else
	#include <chrono>
#endif

#include "configuration.h"

namespace lwlog::details::os
{
	#ifdef _WIN32
		using time_point_t = ::SYSTEMTIME;
	#else
		using time_point_t = std::chrono::system_clock::time_point;
	#endif

	extern const std::int16_t cached_timezone_offset;

	extern const std::array<const char*, 12> month_name;
	extern const std::array<const char*, 12> month_name_short;
	extern const std::array<const char*, 7>	weekday_name;
	extern const std::array<const char*, 7>	weekday_name_short;

	template<typename LocalTimePolicy>
	std::uint8_t handle_timezone(std::uint8_t hour);

	std::string ensure_two_digit_format(std::uint16_t digit);

	struct time_point_base
	{
		time_point_base();

		virtual std::uint16_t millisecond()	const;
		virtual std::uint32_t microsecond()	const;
		virtual std::uint32_t nanosecond() const;

		virtual std::string to_string(std::string_view unit) const;
		virtual std::string to_string(std::uint32_t unit) const;
		virtual std::string build_timestamp(std::uint32_t first_unit, std::uint32_t second_unit, char delimeter) const;
		virtual std::string build_timestamp(std::uint32_t first_unit, std::uint32_t second_unit, 
			std::uint32_t third_unit, char delimeter) const;
		virtual std::string build_timestamp(std::uint32_t first_unit, std::uint32_t second_unit, 
			std::uint32_t third_unit, char delimeter, std::string_view end) const;

		std::uint16_t year;
		std::uint8_t month;
		std::uint8_t weekday;
		std::uint8_t day;
		std::uint8_t hour;
		std::uint8_t minute;
		std::uint8_t second;

		time_point_t now;
	};

	template<typename TimePolicy, 
		typename LocalTimePolicy, typename PreciseUnitsPolicy>
	struct time_point : public time_point_base
	{
		time_point();
	};

	template<typename LocalTimePolicy, typename PreciseUnitsPolicy>
	struct time_point<disable_time, LocalTimePolicy, PreciseUnitsPolicy> : public time_point_base
	{
		time_point() = default;

		std::string to_string(std::string_view unit) const override;
		std::string to_string(std::uint32_t unit) const override;
		std::string build_timestamp(std::uint32_t first_unit, std::uint32_t second_unit, char delimeter) const override;
		std::string build_timestamp(std::uint32_t first_unit, std::uint32_t second_unit,
			std::uint32_t third_unit, char delimeter) const override;
		std::string build_timestamp(std::uint32_t first_unit, std::uint32_t second_unit,
			std::uint32_t third_unit, char delimeter, std::string_view end) const override;
	};

	template<typename LocalTimePolicy>
	struct time_point<enable_time, LocalTimePolicy, enable_precise_units> : public time_point_base
	{
		time_point();

		std::uint16_t millisecond()	const override;
		std::uint32_t microsecond()	const override;
		std::uint32_t nanosecond() const override;

		std::uint16_t m_millisecond;
		std::uint32_t m_microsecond;
		std::uint32_t m_nanosecond;
	};
}

#include "datetime_impl.h"