#include "formatter.h"
#include "formatter_data.h"

namespace lwlog::details
{
	std::string formatter::format(std::string pattern)
	{
		for (const auto& [key, value] : formatter_data::datetime_data)
		{
			const auto& [verbose, shortened] = key;
			if (!verbose.empty())
			{
				while (pattern.find(verbose) != std::string::npos)
				{
					pattern.replace(pattern.find(verbose), verbose.length(), value);
				}
			}
		}

		for (const auto& [key, value] : formatter_data::datetime_data)
		{
			const auto& [verbose, shortened] = key;
			if (!shortened.empty())
			{
				while (pattern.find(shortened) != std::string::npos)
				{
					pattern.replace(pattern.find(shortened), shortened.length(), value);
				}
			}
		}

		return pattern;
	}

	void formatter::format_color(std::string& pattern)
	{
		for (const auto& [key, value] : formatter_data::color_data)
		{
			while (pattern.find(key) != std::string::npos)
			{
				pattern.replace(pattern.find(key), key.length(), value);
			}
		}
	}

	void formatter::insert_pattern_data(std::initializer_list<primitives::attribute_t> attributes)
	{
		for (const auto& [verbose, shortened, value] : attributes)
		{
			formatter_data::datetime_data.insert_or_assign({ verbose, shortened }, value);
		}
	}
}