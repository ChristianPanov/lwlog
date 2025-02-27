#pragma once

#include "argument_format.h"

namespace lwlog::details
{
	template<typename BufferLimits>
	static void format_args(memory_buffer<BufferLimits::message>& message_buffer,
		const char(&args_buffers)[BufferLimits::arg_count][BufferLimits::argument])
	{
		std::size_t pos{ 0 };
		std::size_t buffer_index{ 0 };
		while (pos < message_buffer.size())
		{
			if (message_buffer[pos] == '{' && message_buffer[pos + 1] == '}')
			{
				message_buffer.replace(pos, 2, args_buffers[buffer_index], std::strlen(args_buffers[buffer_index]));
				buffer_index++;
			}
			++pos;
		}
	}
}