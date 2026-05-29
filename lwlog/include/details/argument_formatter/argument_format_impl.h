#pragma once

#include "argument_format.h"

namespace lwlog::details::fmt
{
    template<typename BufferLimits>
    static void format_args_append(memory_buffer<BufferLimits::message>& out, std::string_view fmt,
        const char(&args)[BufferLimits::arg_count][BufferLimits::argument],
        const std::uint16_t* arg_lengths, std::uint8_t arg_count)
    {
        std::size_t pos{ 0 };
        std::size_t last{ 0 };
        std::size_t argument_index{ 0 };

        while(pos + 1 < fmt.size())
        {
            if (fmt[pos] == '{' && fmt[pos + 1] == '}')
            {
                if (pos > last)
                {
                    out.append(fmt.data() + last, pos - last);
                }

                if (argument_index >= arg_count)
                {
                    out.append("{}");
                    pos += 2;
                    last = pos;
                    continue;
                }

                out.append(args[argument_index], arg_lengths[argument_index]);
                ++argument_index;

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

    template<typename BufferLimits>
    void format_arg_typed(memory_buffer<BufferLimits::message>& out, const async_args::argument& arg)
    {
        switch (arg.type)
        {
        case async_args::argument_type::boolean:
        {
            out.append(arg.u.b ? "true" : "false", arg.u.b ? 4 : 5);
            break;
        }
        case async_args::argument_type::character:
        {
            out.append(arg.u.ch);
            break;
        }
        case async_args::argument_type::int64:
        {
            char buffer[32]{};
            const auto result{ std::to_chars(buffer, buffer + sizeof(buffer), arg.u.i64) };
            out.append(buffer, static_cast<std::size_t>(result.ptr - buffer));
            break;
        }
        case async_args::argument_type::uint64:
        {
            char buffer[32]{};
            const auto result{ std::to_chars(buffer, buffer + sizeof(buffer), arg.u.u64) };
            out.append(buffer, static_cast<std::size_t>(result.ptr - buffer));
            break;
        }
        case async_args::argument_type::f32:
        {
            char buffer[32]{};
            const auto result{ std::to_chars(buffer, buffer + sizeof(buffer), arg.u.f32, std::chars_format::general) };
            out.append(buffer, static_cast<std::size_t>(result.ptr - buffer));
            break;
        }
        case async_args::argument_type::f64:
        {
            char buffer[32]{};
            const auto result{ std::to_chars(buffer, buffer + sizeof(buffer), arg.u.f64, std::chars_format::general) };
            out.append(buffer, static_cast<std::size_t>(result.ptr - buffer));
            break;
        }
        case async_args::argument_type::string:
        {
            out.append(arg.u.str.data, arg.u.str.size);
            break;
        }
        }
    }

    template<typename BufferLimits>
    void format_args_typed(memory_buffer<BufferLimits::message>& out, std::string_view fmt, 
        const async_args::captured_args<BufferLimits>& args, std::uint8_t arg_count)
    {
        std::size_t pos{ 0 };
        std::size_t last{ 0 };
        std::size_t argument_index{ 0 };

        while (pos + 1 < fmt.size())
        {
            if (fmt[pos] == '{' && fmt[pos + 1] == '}')
            {
                if (pos > last)
                {
                    out.append(fmt.data() + last, pos - last);
                }

                if (argument_index >= arg_count)
                {
                    out.append("{}");
                    pos += 2;
                    last = pos;
                    continue;
                }

                format_arg_typed<BufferLimits>(out, args.args[argument_index]);
                ++argument_index;

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