#pragma once

#include <cstdint>
#include <array>
#include <charconv>
#include <string_view>

#ifdef _WIN32
	#include "details/windows_lightweight.h"
#else
	#include <ctime>
#endif

namespace lwlog::details::os::datetime
{
	inline const std::array<std::string_view, 12> month_name = { "January", "February", "March", "April", "May",
		"June", "July", "August", "September", "October", "November", "December" };

	inline const std::array<std::string_view, 12> month_name_short = { "Jan", "Feb", "Mar", "Apr", "May","Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	inline const std::array<std::string_view, 7> weekday_name = { "Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday","Friday", "Saturday" };

	inline const std::array<std::string_view, 7> weekday_name_short = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	inline const std::int32_t cached_timezone_offset_minutes = []() -> std::int32_t {
		#ifdef LWLOG_LOCALTIME
            #ifdef _WIN32
                ::TIME_ZONE_INFORMATION time_zone_info{};
                const ::DWORD time_zone_id{ ::GetTimeZoneInformation(&time_zone_info) };

                ::LONG bias_minutes = time_zone_info.Bias;

                if (time_zone_id == TIME_ZONE_ID_DAYLIGHT)
                {
                    bias_minutes += time_zone_info.DaylightBias;
                }
                else if (time_zone_id == TIME_ZONE_ID_STANDARD)
                {
                    bias_minutes += time_zone_info.StandardBias;
                }

                return -static_cast<std::int32_t>(bias_minutes);
            #else
                const ::time_t now_seconds{ ::time(nullptr) };

                ::tm local_time{};
                if (::localtime_r(&now_seconds, &local_time) == nullptr)
                {
                    return 0;
                }
                #if defined(__GLIBC__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
                    return static_cast<std::int32_t>(local_time.tm_gmtoff / 60);
                #else
                    ::tm utc_time{};
                    if (::gmtime_r(&now_seconds, &utc_time) == nullptr)
                    {
                        return 0;
                    }

                    const ::time_t local_epoch{ ::mktime(&local_time) };
                    const ::time_t utc_epoch_as_local{ ::mktime(&utc_time) };

                    const double offset_seconds{ ::difftime(local_epoch, utc_epoch_as_local) };
                    return static_cast<std::int32_t>(offset_seconds / 60.0);
                #endif
            #endif
		#else
			return 0;
		#endif
	}();

	std::uint8_t to_12h(std::uint8_t hour);

    template<std::size_t Size>
    struct timestamp_builder
    {
	public:
		explicit timestamp_builder(char* buffer);

    public:
		template<std::uint8_t Width>
		timestamp_builder& append(std::size_t value);

		timestamp_builder& append_ampm(std::size_t hour);
		timestamp_builder& separate(char separator);

		const char* data() const;
        std::size_t size() const;

    private:
		char* m_buffer;
        std::size_t m_pos{};
    };
}

#include "datetime_utility_impl.h"