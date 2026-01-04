#pragma once

#include <string>

#include "argument_buffers_pool.h"
#include "details/memory_buffer.h"

namespace lwlog::details::fmt
{
    template<typename BufferLimits>
    static void format_args_append(memory_buffer<BufferLimits::message>& out, std::string_view fmt,
        const char(&args)[BufferLimits::arg_count][BufferLimits::argument], 
        const std::uint16_t* arg_lengths, std::uint8_t arg_count);

    template<typename BufferLimits>
    static void format_arg_typed(memory_buffer<BufferLimits::message>& out, const async_args::argument& arg);

    template<typename BufferLimits>
    static void format_args_typed(memory_buffer<BufferLimits::message>& out, std::string_view fmt,
        const async_args::args_slot<BufferLimits>& slot, std::uint8_t arg_count);
}

#include "argument_format_impl.h"