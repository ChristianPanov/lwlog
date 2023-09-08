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

namespace lwlog::details::os
{
    struct time_point
    {
        time_point();

        #if LWLOG_NO_TIME == 0
            std::uint8_t year   {};
            std::uint8_t month  {};
            std::uint8_t weekday{};
            std::uint8_t day    {};
            std::uint8_t hour   {};
            std::uint8_t minute {};
            std::uint8_t second {};

            #if LWLOG_USE_PRECISE_UNITS == 1
                std::uint16_t millisecond{};
                std::uint32_t microsecond{};
                std::uint32_t nanosecond{};
            #endif
        #endif
    };

    class datetime
    {
    public:
        static std::string get_date                 (const time_point& now);
        static std::string get_date_short           (const time_point& now);
        static std::string get_year                 (const time_point& now);
        static std::string get_year_short           (const time_point& now);
        static std::string get_month                (const time_point& now);
        static std::string get_month_name           (const time_point& now);
        static std::string get_month_name_short     (const time_point& now);
        static std::string get_day                  (const time_point& now);
        static std::string get_weekday_name         (const time_point& now);
        static std::string get_weekday_name_short   (const time_point& now);
        static std::string get_time                 (const time_point& now);
        static std::string get_24_hour_clock        (const time_point& now);
        static std::string get_12_hour_clock        (const time_point& now);
        static std::string get_ampm                 (const time_point& now);
        static std::string get_hour_24              (const time_point& now);
        static std::string get_hour_12              (const time_point& now);
        static std::string get_minute               (const time_point& now);
        static std::string get_second               (const time_point& now);
        static std::string get_millisecond          (const time_point& now);
        static std::string get_microsecond          (const time_point& now);
        static std::string get_nanosecond           (const time_point& now);

    private:
        static const char* ampm(std::uint16_t hour);
        static std::uint16_t to_local(std::uint16_t hour);
        static std::uint16_t to_12h(std::uint16_t hour);
        static std::string ensure_two_digit_format(std::uint16_t digit);

    private:
        static const std::int16_t                   m_cached_timezone_offset;
        static const std::array<const char*, 12>    m_month_name;
        static const std::array<const char*, 12>    m_month_name_short;
        static const std::array<const char*, 7>     m_weekday_name;
        static const std::array<const char*, 7>     m_weekday_name_short;
    };
}