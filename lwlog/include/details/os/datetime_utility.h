#pragma once

#include <cstdint>
#include <array>
#include <charconv>

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#else
	#include <ctime>
#endif

namespace lwlog::details::os::datetime
{
	inline const std::array<const char*, 12> month_name = { "January", "February", "March", "April", "May",
		"June", "July", "August", "September", "October", "November", "December" };

	inline const std::array<const char*, 12> month_name_short = { "Jan", "Feb", "Mar", "Apr", "May","Jun",
		"Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };

	inline const std::array<const char*, 7> weekday_name = { "Monday", "Tuesday", "Wednesday",
		"Thursday","Friday", "Saturday", "Sunday" };

	inline const std::array<const char*, 7> weekday_name_short = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

	inline const std::int8_t cached_timezone_offset = []() {
		#ifdef LWLOG_LOCALTIME
			#ifdef _WIN32
					::TIME_ZONE_INFORMATION tz_info;
					::GetTimeZoneInformation(&tz_info);

					::LONG bias{ tz_info.Bias };

					if (tz_info.StandardDate.wMonth != 0)
					{
						bias += tz_info.DaylightBias;
					}

					return -bias / 60;

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
		#else
			return 0;
		#endif
	}();

	static std::uint8_t handle_timezone(std::uint8_t hour);

	static std::uint8_t to_12h(std::uint8_t hour);

    template<std::size_t Size>
    struct timestamp_builder
    {
    public:
		timestamp_builder& append(std::size_t value);
		timestamp_builder& append_ampm(std::size_t hour);
		timestamp_builder& separate(char separator);

		const char* data() const;

    private:
        std::uint64_t m_pos{};
        char m_buffer[Size]{};
    };
}

#include "datetime_utility_impl.h"