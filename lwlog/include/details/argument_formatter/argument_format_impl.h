#pragma once

#include "argument_format.h"

namespace lwlog::details
{
    template<typename BufferLimits>
    static void format_args(memory_buffer<BufferLimits::message>& msg,
        const char(&args)[BufferLimits::arg_count][BufferLimits::argument])
    {
		std::size_t pos{ 0 };
		std::size_t buffer_index{ 0 };
		while (pos < msg.size())
		{
			if (msg[pos] == '{' && msg[pos + 1] == '}')
			{
				msg.replace(pos, 2, args[buffer_index], std::strlen(args[buffer_index]));
				buffer_index++;
			}
			++pos;
		}
    }
}