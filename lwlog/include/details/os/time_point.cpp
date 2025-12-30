#include "time_point.h"

namespace lwlog::details::os
{
    time_point::time_point()
    {
        const raw_timestamp timestamp{ time_point::query_raw_timestamp() };

        nanosecond = timestamp.subsecond_nanoseconds;
        microsecond = timestamp.subsecond_nanoseconds / 1'000U;
        millisecond = timestamp.subsecond_nanoseconds / 1'000'000U;

        const std::int64_t adjusted_unix_seconds = timestamp.unix_seconds + 
            datetime::cached_timezone_offset_minutes * 60;

        date_time_cache& cache{ time_point::thread_local_date_time_cache() };
        if (cache.cached_unix_seconds != adjusted_unix_seconds)
        {
            time_point::update_date_time_cache(cache, adjusted_unix_seconds);
        }

        year = cache.year;
        month = cache.month;
        weekday = cache.weekday;
        day = cache.day;
        hour = cache.hour;
        minute = cache.minute;
        second = cache.second;
    }

    date_time_cache& time_point::thread_local_date_time_cache()
    {
        thread_local date_time_cache cache_instance{};
        return cache_instance;
    }

    void time_point::update_date_time_cache(date_time_cache& cache, std::int64_t unix_seconds_adjusted)
    {
        const std::int64_t days_since_epoch{ unix_seconds_adjusted / seconds_per_day };
        const std::int64_t seconds_into_day{ unix_seconds_adjusted - (days_since_epoch * seconds_per_day) };

        const std::int64_t hours{ seconds_into_day / 3600 };
        const std::int64_t minutes{ (seconds_into_day % 3600) / 60 };
        const std::int64_t seconds{ seconds_into_day % 60 };

        cache.hour = static_cast<std::uint8_t>(hours);
        cache.minute = static_cast<std::uint8_t>(minutes);
        cache.second = static_cast<std::uint8_t>(seconds);

        std::int32_t computed_year{};
        std::int32_t computed_month{};
        std::int32_t computed_day{};
        time_point::civil_from_days(days_since_epoch, computed_year, computed_month, computed_day);

        cache.year = static_cast<std::uint16_t>(computed_year);
        cache.month = static_cast<std::uint8_t>(computed_month);
        cache.day = static_cast<std::uint8_t>(computed_day);

        cache.weekday = static_cast<std::uint8_t>((days_since_epoch + 4) % 7);

        cache.cached_unix_seconds = unix_seconds_adjusted;
    }

    raw_timestamp time_point::query_raw_timestamp()
    {
        #ifdef _WIN32
            ::FILETIME file_time{};
            ::GetSystemTimePreciseAsFileTime(&file_time);

            ::ULARGE_INTEGER combined_ticks{};
            combined_ticks.LowPart = file_time.dwLowDateTime;
            combined_ticks.HighPart = file_time.dwHighDateTime;

            constexpr std::uint64_t unix_epoch_offset_100ns{ 11644473600ULL * 10'000'000ULL };

            const std::uint64_t ticks_100ns_since_unix_epoch{ combined_ticks.QuadPart - unix_epoch_offset_100ns };
            const std::uint32_t subsecond_nanoseconds{ (ticks_100ns_since_unix_epoch % 10'000'000ULL) * 100ULL };

            const std::int64_t unix_seconds = ticks_100ns_since_unix_epoch / 10'000'000ULL;

            return { unix_seconds, subsecond_nanoseconds };
        #else
            ::timespec posix_time{};
            ::clock_gettime(CLOCK_REALTIME, &posix_time);

            return { static_cast<std::int64_t>(posix_time.tv_sec), static_cast<std::uint32_t>(posix_time.tv_nsec) };
        #endif
    }

    void time_point::civil_from_days(std::int64_t days_since_unix_epoch,
        std::int32_t& out_year, std::int32_t& out_month, std::int32_t& out_day)
    {
        const std::int64_t days{ days_since_unix_epoch + 719468 };

        const std::int64_t era{ (days >= 0 ? days : days - 146096) / 146097 };
        const std::int64_t day_of_era{ days - era * 146097 };
        const std::int64_t year_of_era{ (day_of_era - day_of_era / 1460 + day_of_era / 36524 - day_of_era / 146096) / 365 };

        const std::int64_t day_of_year{ day_of_era - (365 * year_of_era + year_of_era / 4 - year_of_era / 100) };
        const std::int64_t month_prime{ (5 * day_of_year + 2) / 153 };

        const std::int64_t day  { day_of_year - (153 * month_prime + 2) / 5 + 1 };
        const std::int64_t month{ month_prime + (month_prime < 10 ? 3 : -9)     };
        const std::int64_t year { year_of_era + era * 400 + (month <= 2)        };

        out_year = static_cast<std::int32_t>(year);
        out_month = static_cast<std::int32_t>(month);
        out_day = static_cast<std::int32_t>(day);
    }
}