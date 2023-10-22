#pragma once

#include <string>

#if LWLOG_NO_FORMATTING == 0
	#if LWLOG_USE_FMT == 1
	    #include <fmt/format.h>
	#elif LWLOG_USE_STD_FORMAT == 1
		#if __cplusplus < 202002L
			#error "std::format is not supported in current cpp standard"
		#else
			#include <format>
		#endif
	#endif
#endif

namespace lwlog::details
{
	using format_args_list = std::initializer_list<const char*>;

	static std::string format_args_impl(std::string_view format, format_args_list args);
	static std::string format_args(std::string_view format, format_args_list args);

	template<typename T> static const char* to_raw_string(T arg);
}

#include "argument_format_impl.h"