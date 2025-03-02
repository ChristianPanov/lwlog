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
	template<typename BufferLimits>
	static void format_args(memory_buffer<BufferLimits::message>& message_buffer,
		const char(&args_buffers)[BufferLimits::arg_count][BufferLimits::argument]);
}

#include "argument_format_impl.h"