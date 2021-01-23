#pragma once

#include <string>
#include <ctime>

#ifdef _WIN64
#include "windows_lightweight.h"
#include <array>
#else
#include <chrono>
#endif

namespace lwlog::details::datetime
{
#ifdef _WIN64
    using time_point_t = SYSTEMTIME;
    static void init_time_point(time_point_t& time_point)
    {
        GetSystemTime(&time_point);
    }
#else
    using time_point_t = std::chrono::system_clock::time_point;
    static void init_time_point(time_point_t& time_point)
    {
        time_point = std::chrono::system_clock::now();
    }
#endif
}

namespace lwlog::details::datetime
{
#ifdef LWLOG_USE_LOCALTIME
#ifdef _WIN64
    static int timezone_offset()
    {
        auto offset_epoch = std::localtime(new std::time_t(0));
        return offset_epoch->tm_hour;
    }
    static auto g_cached_timezone_offset = timezone_offset();
#else
    static std::tm* time_standard(const std::time_t* time) { return std::localtime(time); }
#endif
#else
#ifdef _WIN64
    static int timezone_offset() { return 0; }
    static auto g_cached_timezone_offset = timezone_offset();
#else
    static std::tm* time_standard(const std::time_t* time) { return std::gmtime(time); }
#endif
#endif
}

namespace lwlog::details::datetime
{
#ifdef _WIN64
    static const std::array<const char*, 12> month = { "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December" };

    static const std::array<const char*, 12> month_abbreviated = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };

    static const std::array<const char*, 7> weekday = { "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday", "Sunday" };

    static const std::array<const char*, 7> weekday_abbreviated = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

    static const char* ampm(std::uint16_t hour)
    {
        return hour >= 12 ? "pm" : "am";
    }

    static std::uint16_t to_12h(std::uint16_t hour)
    {
        return hour > 12 ? hour - 12 : hour;
    }

    static std::uint16_t to_local(std::uint16_t hour)
    {
        int local = hour + g_cached_timezone_offset;
        if (local <= 23) return local;
        else {
            return local - 24;
        }
    }

    static std::string pad_with_zero_if_needed(std::uint16_t digit)
    {
        return (digit <= 9 ? "0" : "") + std::to_string(digit);
    }

    static std::string get_date(time_point_t now)
    {
        return std::to_string(now.wYear) + "-" +
            std::to_string(now.wMonth) + "-" +
            std::to_string(now.wDay);
    }

    static std::string get_date_short(time_point_t now)
    {
        return pad_with_zero_if_needed(now.wMonth) + "/"
            + pad_with_zero_if_needed(now.wDay) + "/"
            + pad_with_zero_if_needed(now.wYear % 100);
    }

    static std::string get_year(time_point_t now)
    {
        return std::to_string(now.wYear);
    }

    static std::string get_year_short(time_point_t now)
    {
        return pad_with_zero_if_needed(now.wYear % 100);
    }

    static std::string get_month(time_point_t now)
    {
        return pad_with_zero_if_needed(now.wMonth);
    }

    static std::string get_month_name(time_point_t now)
    {
        return month[now.wMonth - 1];
    }

    static std::string get_month_name_short(time_point_t now)
    {
        return month_abbreviated[now.wMonth - 1];
    }

    static std::string get_day(time_point_t now)
    {
        return pad_with_zero_if_needed(now.wDay);
    }

    static std::string get_weekday_name(time_point_t now)
    {
        return weekday[now.wDayOfWeek - 1];
    }

    static std::string get_weekday_name_short(time_point_t now)
    {
        return weekday_abbreviated[now.wDayOfWeek - 1];
    }

    static std::string get_time(time_point_t now)
    {
        return pad_with_zero_if_needed(to_local(now.wHour)) + ":" +
            pad_with_zero_if_needed(now.wMinute) + ":" +
            pad_with_zero_if_needed(now.wSecond);
    }

    static std::string get_24_hour_clock(time_point_t now)
    {
        return pad_with_zero_if_needed(to_local(now.wHour)) + ":" +
            pad_with_zero_if_needed(now.wMinute);
    }

    static std::string get_12_hour_clock(time_point_t now)
    {
        return pad_with_zero_if_needed(to_12h(to_local(now.wHour))) + ":" +
            pad_with_zero_if_needed(now.wMinute) + ":" +
            pad_with_zero_if_needed(now.wSecond) + ampm(now.wHour);
    }

    static std::string get_ampm(time_point_t now)
    {
        return ampm(to_local(now.wHour));
    }

    static std::string get_hour_24(time_point_t now)
    {
        return pad_with_zero_if_needed(to_local(now.wHour));
    }

    static std::string get_hour_12(time_point_t now)
    {
        return pad_with_zero_if_needed(to_12h(to_local(now.wHour)));
    }

    static std::string get_minute(time_point_t now)
    {
        return pad_with_zero_if_needed(now.wMinute);
    }

    static std::string get_second(time_point_t now)
    {
        return pad_with_zero_if_needed(now.wSecond);
    }
#else
    static std::string format_time(const char* format, time_point_t now)
    {
        char buff[256];
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::strftime(buff, sizeof(buff), format, time_standard(&in_time_t));
        return buff;
    }

    static std::string get_date(time_point_t now) { return format_time("%F", now); }
    static std::string get_date_short(time_point_t now) { return format_time("%D", now); }
    static std::string get_year(time_point_t now) { return format_time("%Y", now); }
    static std::string get_year_short(time_point_t now) { return format_time("%y", now); }
    static std::string get_month(time_point_t now) { return format_time("%m", now); }
    static std::string get_month_name(time_point_t now) { return format_time("%B", now); }
    static std::string get_month_name_short(time_point_t now) { return format_time("%b", now); }
    static std::string get_day(time_point_t now) { return format_time("%d", now); }
    static std::string get_weekday_name(time_point_t now) { return format_time("%A", now); }
    static std::string get_weekday_name_short(time_point_t now) { return format_time("%a", now); }
    static std::string get_time(time_point_t now) { return format_time("%T", now); }
    static std::string get_24_hour_clock(time_point_t now) { return format_time("%R", now); }
    static std::string get_12_hour_clock(time_point_t now) { return format_time("%r", now); }
    static std::string get_ampm(time_point_t now) { return format_time("%p", now); }
    static std::string get_hour_24(time_point_t now) { return format_time("%H", now); }
    static std::string get_hour_12(time_point_t now) { return format_time("%I", now); }
    static std::string get_minute(time_point_t now) { return format_time("%M", now); }
    static std::string get_second(time_point_t now) { return format_time("%S", now); }
#endif
}