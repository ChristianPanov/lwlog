#pragma once

#include <string>

#include "details/memory_buffer.h"

namespace lwlog::details
{
    template<typename BufferLimits>
    static void format_args_append(memory_buffer<BufferLimits::message>& out, std::string_view fmt,
        const char(&args)[BufferLimits::arg_count][BufferLimits::argument], 
        const std::uint16_t* arg_lengths, std::uint8_t arg_count);
}

#include "argument_format_impl.h"