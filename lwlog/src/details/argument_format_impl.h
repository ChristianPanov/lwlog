#pragma once

#include "argument_format.h"

namespace lwlog::details
{
	static void format_args(memory_buffer<256>& message_buffer, char(&args_buffer)[10][24])
	{
		std::size_t pos{ 0 };
		std::size_t buffer_index{ 0 };
		while (pos < message_buffer.size())
		{
			if (message_buffer[pos] == '{' && message_buffer[pos + 1] == '}')
			{
				message_buffer.replace(pos, 2, args_buffer[buffer_index++], std::strlen(args_buffer[buffer_index]));
			}
			++pos;
		}
	}
}