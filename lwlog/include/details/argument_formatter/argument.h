#pragma once

#include <cstdint>

namespace lwlog::details::log_args
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

    template<typename BufferLimits>
    struct captured_args
    {
        template<typename T>
        void set(std::uint8_t index, T&& value);

        argument args[BufferLimits::arg_count];
        char string_storage[BufferLimits::arg_count][BufferLimits::argument];
    };

    template<typename BufferLimits, typename... Args>
    std::uint8_t capture_args(captured_args<BufferLimits>& out, Args&&... args);
}

#include "argument_impl.h"