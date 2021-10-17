#pragma once

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
			details::pattern::drop_color_flags(pattern);
		}
	};
}