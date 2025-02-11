#include "datetime_utility.h"
#pragma once

namespace lwlog::details::os::datetime
{
    template<typename LocalTimePolicy>
    std::uint8_t handle_timezone(std::uint8_t hour)
    {
        return hour;
    }

    template <>
    std::uint8_t handle_timezone<enable_local_time>(std::uint8_t hour)
    {
        hour += cached_timezone_offset<enable_local_time>;
        hour = (hour <= 23) ? hour : hour - 24;

        return hour;
    }

    static std::uint8_t to_12h(std::uint8_t hour)
    {
        return hour > 12 ? hour - 12 : hour;
    }

    static std::string ensure_two_digit_format(std::uint32_t digit)
    {
        return (digit <= 9 ? "0" : "") + std::to_string(digit);
    }
}
