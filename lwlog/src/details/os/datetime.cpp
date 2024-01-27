#include "datetime.h"

namespace lwlog::details::os
{
	static const std::int16_t cached_timezone_offset = []() {
		#ifdef _WIN32
			::TIME_ZONE_INFORMATION tz_info;
			::DWORD result{ ::GetTimeZoneInformation(&tz_info) };

			return -tz_info.Bias / 60;
		#else
			const auto offset_epoch{ std::localtime(new std::time_t(0)) };
			return offset_epoch->tm_hour;
		#endif
	}();

	std::string ensure_two_digit_format(std::uint16_t digit)
	{
		return (digit <= 9 ? "0" : "") + std::to_string(digit);
	}

	time_point_base::time_point_base()
	{
		#if LWLOG_NO_TIME == 0
			#ifdef _WIN32
				::GetSystemTime(&now);
				
				year	= now.wYear;
				month	= now.wMonth;
				weekday	= now.wDayOfWeek;
				day		= now.wDay;
				hour	= now.wHour;
				minute	= now.wMinute;
				second	= now.wSecond;
			#else
				now = std::chrono::system_clock::now();
				const std::time_t now_time_t{ std::chrono::system_clock::to_time_t(now) };
				const std::tm* details{ std::gmtime(&now_time_t) };

				year	= details->tm_year + 1900;
				month	= details->tm_mon + 1;
				weekday	= details->tm_wday;
				day		= details->tm_mday;
				hour	= details->tm_hour;
				minute	= details->tm_min;
				second	= details->tm_sec;
			#endif
		#endif
	}

	std::uint16_t time_point_base::millisecond() const 
	{ 
		return {}; 
	}

	std::uint32_t time_point_base::microsecond() const 
	{ 
		return {}; 
	}

	std::uint32_t time_point_base::nanosecond()	const 
	{ 
		return {}; 
	}

	std::string time_point_base::to_string(std::string_view unit) const
	{
		return unit.data();
	}

	std::string time_point_base::to_string(std::uint32_t unit) const
	{
		return ensure_two_digit_format(unit);
	}	
	
	std::string time_point_base::build_timestamp(std::uint32_t first_unit,
		std::uint32_t second_unit, char delimeter) const
	{
		return ensure_two_digit_format(first_unit) + delimeter
			+ ensure_two_digit_format(second_unit);
	}

	std::string time_point_base::build_timestamp(std::uint32_t first_unit, 
		std::uint32_t second_unit, std::uint32_t third_unit, char delimeter) const
	{
		return ensure_two_digit_format(first_unit) + delimeter
			+ ensure_two_digit_format(second_unit) + delimeter
			+ ensure_two_digit_format(third_unit);
	}

	std::string time_point_base::build_timestamp(std::uint32_t first_unit, 
		std::uint32_t second_unit, std::uint32_t third_unit, char delimeter, std::string_view end) const
	{
		return build_timestamp(first_unit, second_unit, third_unit, delimeter) + end.data();
	}

	const std::array<const char*, 12> month_name = {
	"January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December" };

	const std::array<const char*, 12> month_name_short = {
		"Jan", "Feb", "Mar", "Apr", "May","Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };

	const std::array<const char*, 7> weekday_name = {
		"Monday", "Tuesday", "Wednesday", "Thursday","Friday", "Saturday", "Sunday" };

	const std::array<const char*, 7> weekday_name_short = {
		"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
}