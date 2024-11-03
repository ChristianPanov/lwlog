#pragma once

#include <cstdint>
#include <array>
#include <string>

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#else
	#include <ctime>
#endif

#include "configuration.h"

namespace lwlog::details::os::datetime
{
	inline const std::array<const char*, 12> month_name = { "January", "February", "March", "April", "May",
		"June", "July", "August", "September", "October", "November", "December" };

	inline const std::array<const char*, 12> month_name_short = { "Jan", "Feb", "Mar", "Apr", "May","Jun",
		"Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };

	inline const std::array<const char*, 7> weekday_name = { "Monday", "Tuesday", "Wednesday",
		"Thursday","Friday", "Saturday", "Sunday" };

	inline const std::array<const char*, 7> weekday_name_short = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

	template<typename LocalTimePolicy>
	inline const std::int8_t cached_timezone_offset = 0;

	template<>
	inline const std::int8_t cached_timezone_offset<enable_local_time> = []() {
		#ifdef _WIN32
			::TIME_ZONE_INFORMATION tz_info;
			::GetTimeZoneInformation(&tz_info);

			return -tz_info.Bias / 60;
		#else
			const std::time_t now{ std::time(nullptr) };

			std::tm gm_time;
			std::tm local_time;

			gmtime_r(&now, &gm_time);
			localtime_r(&now, &local_time);

			const std::time_t local_epoch{ std::mktime(&local_time) };
			const std::time_t gm_epoch{ std::mktime(&gm_time) };

			const std::int8_t difference{ static_cast<std::int8_t>(
				std::difftime(local_epoch, gm_epoch) / 3600) 
			};

			return difference;
		#endif
	}();

	template<typename LocalTimePolicy>
	static std::uint8_t handle_timezone(std::uint8_t hour);

	static std::uint8_t to_12h(std::uint8_t hour);

	static std::string ensure_two_digit_format(std::uint32_t digit);
}

#include "datetime_utility_impl.h"