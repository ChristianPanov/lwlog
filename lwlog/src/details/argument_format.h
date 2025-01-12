#pragma once

#include <string>

#include "details/memory_buffer.h"

#if __cplusplus < 202002L
	#ifdef FMT_VERSION
		#include <fmt/format.h>
	#endif
#else
	#include <format>
#endif

namespace lwlog::details
{
	static void format_args(memory_buffer<256>& message_buffer, char(&args_buffer)[10][24]);
}

#include "argument_format_impl.h"