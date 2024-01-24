#pragma once

#include <string>
#include <array>
#include <ctime>

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

	extern const std::int16_t m_cached_timezone_offset;

	template<typename LocalTimePolicy>
	std::uint8_t handle_timezone(std::uint8_t hour);

	struct time_point_base
	{
		time_point_base();

		virtual std::uint16_t millisecond()	const;
		virtual std::uint32_t microsecond()	const;
		virtual std::uint32_t nanosecond() const;

		std::uint16_t year;
		std::uint8_t month;
		std::uint8_t weekday;
		std::uint8_t day;
		std::uint8_t hour;
		std::uint8_t minute;
		std::uint8_t second;

		time_point_t now;
	};

	template<typename LocalTimePolicy, typename PreciseUnitsPolicy>
	struct time_point : public time_point_base
	{
		time_point();
	};

	template<typename LocalTimePolicy>
	struct time_point<LocalTimePolicy, enable_precise_units> : public time_point_base
	{
		time_point();

		std::uint16_t millisecond()	const override;
		std::uint32_t microsecond()	const override;
		std::uint32_t nanosecond() const override;

		std::uint16_t m_millisecond;
		std::uint32_t m_microsecond;
		std::uint32_t m_nanosecond;
	};

	class datetime
	{
	public:
		static std::string get_date					(const time_point_base& now);
		static std::string get_date_short			(const time_point_base& now);
		static std::string get_year					(const time_point_base& now);
		static std::string get_year_short			(const time_point_base& now);
		static std::string get_month				(const time_point_base& now);
		static std::string get_month_name			(const time_point_base& now);
		static std::string get_month_name_short		(const time_point_base& now);
		static std::string get_day					(const time_point_base& now);
		static std::string get_weekday_name			(const time_point_base& now);
		static std::string get_weekday_name_short	(const time_point_base& now);
		static std::string get_time					(const time_point_base& now);
		static std::string get_24_hour_clock		(const time_point_base& now);
		static std::string get_12_hour_clock		(const time_point_base& now);
		static std::string get_ampm					(const time_point_base& now);
		static std::string get_hour_24				(const time_point_base& now);
		static std::string get_hour_12				(const time_point_base& now);
		static std::string get_minute				(const time_point_base& now);
		static std::string get_second				(const time_point_base& now);
		static std::string get_millisecond			(const time_point_base& now);
		static std::string get_microsecond			(const time_point_base& now);
		static std::string get_nanosecond			(const time_point_base& now);

	private:
		static const char* ampm(std::uint16_t hour);
		static std::uint16_t to_12h(std::uint16_t hour);
		static std::string ensure_two_digit_format(std::uint16_t digit);

	private:
		static const std::array<const char*, 12> m_month_name;
		static const std::array<const char*, 12> m_month_name_short;
		static const std::array<const char*, 7>	m_weekday_name;
		static const std::array<const char*, 7>	m_weekday_name_short;
	};
}

#include "datetime_impl.h"