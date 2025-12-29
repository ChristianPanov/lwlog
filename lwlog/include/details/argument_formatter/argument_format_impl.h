#pragma once

#include "argument_format.h"

namespace lwlog::details
{
    template<typename BufferLimits>
    static void format_args_append(memory_buffer<BufferLimits::message>& out, std::string_view fmt,
        const char(&args)[BufferLimits::arg_count][BufferLimits::argument],
        const std::uint16_t* arg_lengths, std::uint8_t arg_count)
    {
        std::size_t pos{ 0 };
        std::size_t last{ 0 };
        std::size_t argument_index{ 0 };

        while(pos < fmt.size())
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
}