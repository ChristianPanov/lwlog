#pragma once

#include <cstdint>
#include <array>
#include <string>

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#else
	#include <chrono>
#endif

#include "configuration.h"

namespace lwlog::details::os::datetime
{
	static const std::int16_t cached_timezone_offset = []() {
		#ifdef _WIN32
			::TIME_ZONE_INFORMATION tz_info;
			::GetTimeZoneInformation(&tz_info);

			return -tz_info.Bias / 60;
		#else
			const auto offset_epoch{ std::localtime(new std::time_t(0)) };
			return offset_epoch->tm_hour;
		#endif
	}();

	static const std::array<const char*, 12> month_name = { "January", "February", "March", "April", "May", 
		"June", "July", "August", "September", "October", "November", "December" };

	static const std::array<const char*, 12> month_name_short = { "Jan", "Feb", "Mar", "Apr", "May","Jun", 
		"Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };

	static const std::array<const char*, 7> weekday_name = { "Monday", "Tuesday", "Wednesday", 
		"Thursday","Friday", "Saturday", "Sunday" };

	static const std::array<const char*, 7> weekday_name_short = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

	template<typename LocalTimePolicy>
	static std::uint8_t handle_timezone(std::uint8_t hour);

	static std::uint16_t to_12h(std::uint16_t hour);

	static std::string ensure_two_digit_format(std::uint16_t digit);
}

#include "datetime_utility_impl.h"