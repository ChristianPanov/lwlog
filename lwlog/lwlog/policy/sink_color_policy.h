#pragma once

#include <string>

#include "details/pattern/pattern.h"

namespace lwlog
{
	struct colored_policy
	{
		static void process_color(std::string& pattern) 
		{
			details::pattern::compile_colors(pattern);
		}
	};

	struct uncolored_policy 
	{
		static void process_color(std::string& pattern)
		{
			while (pattern.find('^') != std::string::npos)
			{
				auto first_pos = pattern.find_first_of('^');
				auto last_pos = pattern.find('^', first_pos + 1);
				pattern.erase(first_pos, last_pos - first_pos + 1);
			}
		}
	};
}