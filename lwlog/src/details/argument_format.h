#pragma once

#include <string>

#ifdef LWLOG_NO_FORMATTING
	#if __cplusplus < 202002L
		#ifdef FMT_VERSION
			#include <fmt/format.h>
		#endif
	#else
		#include <format>
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