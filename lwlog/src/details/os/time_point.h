#pragma once

#include <string>
#include <ctime>

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#else
	#include <chrono>
#endif

#include "configuration.h"
#include "datetime_utility.h"

namespace lwlog::details::os
{
	#ifdef _WIN32
		using time_point_t = ::SYSTEMTIME;
	#else
		using time_point_t = std::chrono::system_clock::time_point;
	#endif

	class time_point_base
	{
	public:
		time_point_base();

	public:
		virtual std::uint16_t millisecond()	const;
		virtual std::uint32_t microsecond()	const;
		virtual std::uint32_t nanosecond() const;
		virtual std::string ampm() const;

	public:
		virtual std::string to_string(std::string_view unit) const;
		virtual std::string to_string(std::uint32_t unit) const;

		virtual std::string build_timestamp(std::uint32_t first_unit, 
			std::uint32_t second_unit, char delimeter) const;
		virtual std::string build_timestamp(std::uint32_t first_unit, 
			std::uint32_t second_unit, std::uint32_t third_unit, char delimeter) const;

	public:
		std::uint16_t year;
		std::uint8_t month;
		std::uint8_t weekday;
		std::uint8_t day;
		std::uint8_t hour;
		std::uint8_t minute;
		std::uint8_t second;

	protected:
		time_point_t now;
	};

	template<typename TimePolicy, typename LocalTimePolicy, typename PreciseUnitsPolicy>
	class time_point : public time_point_base
	{
	public:
		time_point();
	};

	template<typename LocalTimePolicy, typename PreciseUnitsPolicy>
	class time_point<disable_time, LocalTimePolicy, PreciseUnitsPolicy> 
		: public time_point_base
	{
	public:
		time_point() = default;

	public:
		std::string ampm() const override;
		std::string to_string(std::string_view unit) const override;
		std::string to_string(std::uint32_t unit) const override;

		std::string build_timestamp(std::uint32_t first_unit, 
			std::uint32_t second_unit, char delimeter) const override;
		std::string build_timestamp(std::uint32_t first_unit, 
			std::uint32_t second_unit, std::uint32_t third_unit, char delimeter) const override;
	};

	template<typename LocalTimePolicy>
	class time_point<enable_time, LocalTimePolicy, enable_precise_units> 
		: public time_point_base
	{
	public:
		time_point();

	public:
		std::uint16_t millisecond()	const override;
		std::uint32_t microsecond()	const override;
		std::uint32_t nanosecond() const override;

	private:
		std::uint16_t m_millisecond;
		std::uint32_t m_microsecond;
		std::uint32_t m_nanosecond;
	};
}

#include "time_point_impl.h"