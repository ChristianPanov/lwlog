#pragma once

#include <cstdint>

#include "datetime_utility.h"

#ifdef _WIN32
#include "details/windows_lightweight.h"
#else
#include <time.h>
#endif

namespace lwlog::details::os
{
    struct raw_timestamp
    {
        std::int64_t unix_seconds;
        std::uint32_t subsecond_nanoseconds;
    };

    struct date_time_cache
    {
        std::int64_t cached_unix_seconds{ 0x7FFF'FFFF'FFFF'FFFFLL };

        std::uint16_t year{};
        std::uint8_t  month{};
        std::uint8_t  weekday{};
        std::uint8_t  day{};
        std::uint8_t  hour{};
        std::uint8_t  minute{};
        std::uint8_t  second{};
    };

    struct time_point
    {
        time_point();

        std::uint16_t year{};
        std::uint8_t  month{};
        std::uint8_t  weekday{};
        std::uint8_t  day{};
        std::uint8_t  hour{};
        std::uint8_t  minute{};
        std::uint8_t  second{};

        std::uint16_t millisecond{};
        std::uint32_t microsecond{};
        std::uint32_t nanosecond{};

    private:
        static date_time_cache& thread_local_date_time_cache();
        static void update_date_time_cache(date_time_cache& cache, std::int64_t unix_seconds_adjusted);
        static raw_timestamp query_raw_timestamp();

    private:
        static constexpr std::int64_t seconds_per_day{ 86'400 };

        static void civil_from_days(std::int64_t days_since_unix_epoch,
            std::int32_t& out_year,
            std::int32_t& out_month,
            std::int32_t& out_day);
    };
}