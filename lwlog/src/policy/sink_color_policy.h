#pragma once

#include "details/pattern/color_compiler.h"

namespace lwlog
{
	struct colored_policy
	{
		static void process_color(std::string& pattern) 
		{
			details::color_compiler::compile(pattern);
		}
	};

	struct uncolored_policy 
	{
		static void process_color(std::string& pattern)
		{
			details::color_compiler::drop_flags(pattern);
		}
	};
}