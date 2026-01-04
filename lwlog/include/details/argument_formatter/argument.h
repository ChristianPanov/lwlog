#pragma once

#include <cstdint>

namespace lwlog::details::async_args
{
    enum class argument_type : std::uint8_t
    {
        boolean,
        character,
        int64,
        uint64,
        f32,
        f64,
        string
    };

    struct string_ref
    {
        const char* data;
        std::uint16_t size;
    };

    struct argument
    {
        argument_type type;

        union
        {
            bool b;
            char ch;
            std::int64_t i64;
            std::uint64_t u64;
            float f32;
            double f64;

            string_ref str;
        } u;
    };
}