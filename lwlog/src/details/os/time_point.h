#pragma once

#ifdef _WIN32
    #include "details/windows_lightweight.h"
#else
    #include <chrono>
#endif

#include "configuration.h"
#include "datetime_utility.h"

namespace lwlog::details::os
{
    class time_point_base
    {
    public:
        virtual ~time_point_base() = default;

    public:
        std::uint16_t year;
        std::uint8_t month;
        std::uint8_t weekday;
        std::uint8_t day;
        std::uint8_t hour;
        std::uint8_t minute;
        std::uint8_t second;
        std::uint16_t millisecond;
        std::uint32_t microsecond;
        std::uint32_t nanosecond;
    };

    template<typename LocalTimePolicy>
    class time_point : public time_point_base
    {
    public:
        time_point();
    };
}

#include "time_point_impl.h"
