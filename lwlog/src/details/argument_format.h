#pragma once

#include <string>

namespace lwlog::details
{
	using format_args_list = std::initializer_list<const char*>;

	static std::string format_arguments(std::string_view format, format_args_list args);

	template<typename T> static const char* to_raw_string(T arg);
}

#include "argument_format_impl.h"