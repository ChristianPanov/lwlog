#pragma once

#include <string>

#include "details/formatter/formatter.h"

namespace lwlog
{
	struct colored_policy
	{
		static std::string process_color(std::string_view pattern) 
		{
			return details::formatter::format_color(pattern.data());
		}
	};

	struct uncolored_policy 
	{
		static std::string process_color(std::string_view pattern)
		{
			std::string res = pattern.data();
			while (res.find('^') != std::string::npos)
			{
				auto first_pos = res.find_first_of('^');
				auto last_pos = res.find('^', first_pos + 1);
				res.erase(first_pos, last_pos - first_pos + 1);
			}
			return res;
		}
	};
}