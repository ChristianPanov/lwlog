#pragma once

#include <string>

namespace lwlog::details
{
	using format_args_list = std::initializer_list<const char*>;

	static std::string format_arguments(std::string_view format, format_args_list args);

	template<typename T> static const char* to_raw_string(T arg);
}

#include "argument_format_impl.h"

#if LWLOG_NO_FORMATTING == 1
	#define LWLOG_FORMAT_FN(x, ...) x
#else
	#if LWLOG_USE_FMT == 1
		#include <fmt/format.h>
		#define LWLOG_FORMAT_FN(x, ...) fmt::format(x, __VA_ARGS__)
	#elif LWLOG_USE_STD_FORMAT == 1
		#if __cplusplus < 202002L
			#error "std::format is not supported in current cpp standard"
		#else
			#include <format>
			#define LWLOG_FORMAT_FN(x, ...) std::format(x, __VA_ARGS__)
		#endif
	#else
		#define LWLOG_FORMAT_FN(x, ...) lwlog::details::format_arguments(x, __VA_ARGS__)
	#endif
#endif