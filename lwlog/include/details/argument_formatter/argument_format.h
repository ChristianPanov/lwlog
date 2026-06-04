#pragma once

#include <string>

#include "argument.h"
#include "details/memory_buffer.h"

namespace lwlog::details::fmt
{
    template<typename BufferLimits>
    static void format_arg_typed(memory_buffer<BufferLimits::message>& out, const log_args::argument& arg);

    template<typename BufferLimits>
    static void format_args_typed(memory_buffer<BufferLimits::message>& out, std::string_view fmt,
        const log_args::captured_args<BufferLimits>& args, std::uint8_t arg_count);
}

#include "argument_format_impl.h"