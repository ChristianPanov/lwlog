#include "formatter.h"
#include "formatter_data.h"

namespace lwlog::details
{
	std::string formatter::format(std::string pattern)
	{
		if ((strstr(pattern.data(), "{")) && (strstr(pattern.data(), "}")))
		{
			for (const auto& [key, value] : formatter_data::datetime_data)
			{
				const auto& [verbose, shortened] = key;
				if (!verbose.empty())
				{
					while (strstr(pattern.data(), verbose.data()))
					{
						pattern.replace(pattern.find(verbose), verbose.length(), value);
					}
				}
			}
		}

		if (strstr(pattern.data(), "%"))
		{
			for (const auto& [key, value] : formatter_data::datetime_data)
			{
				const auto& [verbose, shortened] = key;
				if (!shortened.empty())
				{
					while (strstr(pattern.data(), shortened.data()))
					{
						pattern.replace(pattern.find(shortened), shortened.length(), value);
					}
				}
			}
		}

		return pattern;
	}

	void formatter::format_color(std::string& pattern)
	{
		if (strstr(pattern.data(), "^"))
		{
			for (const auto& [key, value] : formatter_data::color_data)
			{
				while (strstr(pattern.data(), key.data()))
				{
					pattern.replace(pattern.find(key), key.length(), value);
				}
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