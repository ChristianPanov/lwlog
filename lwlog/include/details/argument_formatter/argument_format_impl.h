#pragma once

#include "argument_format.h"

namespace lwlog::details::fmt
{
    template<typename BufferLimits, std::size_t Capacity>
    void format_next_arg(memory_buffer<BufferLimits::message>& out, 
        const log_args::argument_buffer<Capacity>& args, std::size_t& cursor)
    {
        switch (args.decode_type(cursor))
        {
        case log_args::argument_type::boolean:
        {
            const bool value{ args.template decode_scalar<bool>(cursor) };
            out.append(value ? "true" : "false", value ? 4 : 5);
            break;
        }
        case log_args::argument_type::character:
        {
            out.append(args.template decode_scalar<char>(cursor));
            break;
        }
        case log_args::argument_type::int64:
        {
            const std::int64_t value{ args.template decode_scalar<std::int64_t>(cursor) };

            char buffer[24];
            const auto result{ std::to_chars(buffer, buffer + sizeof(buffer), value) };
            out.append(buffer, static_cast<std::size_t>(result.ptr - buffer));
            break;
        }
        case log_args::argument_type::uint64:
        {
            const std::uint64_t value{ args.template decode_scalar<std::uint64_t>(cursor) };

            char buffer[24];
            const auto result{ std::to_chars(buffer, buffer + sizeof(buffer), value) };
            out.append(buffer, static_cast<std::size_t>(result.ptr - buffer));
            break;
        }
        case log_args::argument_type::f32:
        {
            const float value{ args.template decode_scalar<float>(cursor) };

            char buffer[32];
            const auto result{ std::to_chars(buffer, buffer + sizeof(buffer), value) };
            out.append(buffer, static_cast<std::size_t>(result.ptr - buffer));
            break;
        }
        case log_args::argument_type::f64:
        {
            const double value{ args.template decode_scalar<double>(cursor) };

            char buffer[32];
            const auto result{ std::to_chars(buffer, buffer + sizeof(buffer), value) };
            out.append(buffer, static_cast<std::size_t>(result.ptr - buffer));
            break;
        }
        case log_args::argument_type::string:
        {
            std::string_view value{ args.decode_string(cursor) };
            out.append(value);
            break;
        }
        }
    }

    template<typename BufferLimits, std::size_t Capacity>
    void format_args_typed(memory_buffer<BufferLimits::message>& out, std::string_view fmt, 
        const log_args::argument_buffer<Capacity>& args, std::uint8_t arg_count)
    {
        std::size_t cursor{ 0 };
        std::uint8_t consumed{ 0 };

        std::size_t pos{ 0 };
        std::size_t last{ 0 };

        while (pos + 1 < fmt.size())
        {
            if (fmt[pos] == '{' && fmt[pos + 1] == '}')
            {
                if (pos > last)
                {
                    out.append(fmt.data() + last, pos - last);
                }

                if (consumed < arg_count)
                {
                    format_next_arg<BufferLimits>(out, args, cursor);
                    ++consumed;
                }
                else
                {
                    out.append("{}", 2);
                }

                pos += 2;
                last = pos;
                continue;
            }
            ++pos;
        }

        if (last < fmt.size())
        {
            out.append(fmt.data() + last, fmt.size() - last);
        }
    }
}