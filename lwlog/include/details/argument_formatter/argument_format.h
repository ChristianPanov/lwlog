#pragma once

#include "argument_buffer.h"
#include "details/memory_buffer.h"

namespace lwlog::details::fmt
{
    template<typename BufferLimits, std::size_t Capacity>
    static void format_next_arg(memory_buffer<BufferLimits::message>& out, 
        const log_args::argument_buffer<Capacity>& args, std::size_t& cursor);

    template<typename BufferLimits, std::size_t Capacity>
    static void format_args_typed(memory_buffer<BufferLimits::message>& out, std::string_view fmt,
        const log_args::argument_buffer<Capacity>& args, std::uint8_t arg_count);
}

#include "argument_format_impl.h"