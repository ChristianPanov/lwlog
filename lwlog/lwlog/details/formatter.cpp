#include "formatter.h"
#include "formatter_data.h"

namespace lwlog::details
{
	std::string formatter::format(std::string pattern, bool should_color)
	{
		for (const auto& [key, value] : m_pattern_data)
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

		for (const auto& [key, value] : m_pattern_data)
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

		for (const auto& [key, value] : m_color_data)
		{
			while (pattern.find(key) != std::string::npos)
			{
				pattern.replace(pattern.find(key), key.length(), (should_color == true ? value : ""));
			}
		}

		return pattern;
	}

	void formatter::insert_pattern_data(std::initializer_list<attribute_t> attributes)
	{
		for (const auto& [verbose, shortened, value] : attributes)
		{
			m_pattern_data.insert_or_assign({ verbose, shortened }, value);
		}
	}

	formatter::pattern_map formatter::m_pattern_data{ formatter_data::pattern_data };
	formatter::color_map formatter::m_color_data{ formatter_data::color_data };
}