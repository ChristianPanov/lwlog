#include "formatter.h"
#include "formatter_data.h"

namespace lwlog::details
{
	std::string formatter::format(std::string pattern, bool should_color)
	{
		for (const auto& [key, attribute] : m_pattern_data)
		{
			const auto& [verbose, shortened] = key;
			if (!verbose.empty())
			{
				while (pattern.find(verbose) != std::string::npos)
				{
					pattern.replace(pattern.find(verbose), verbose.length(), attribute);
				}
			}
		}

		for (const auto& [key, attribute] : m_pattern_data)
		{
			const auto& [verbose, shortened] = key;
			if (!shortened.empty())
			{
				while (pattern.find(shortened) != std::string::npos)
				{
					pattern.replace(pattern.find(shortened), shortened.length(), attribute);
				}
			}
		}

		for (const auto& [key, attribute] : m_color_data)
		{
			while (pattern.find(key) != std::string::npos)
			{
				pattern.replace(pattern.find(key), key.length(), (should_color == true ? attribute : ""));
			}
		}

		return pattern;
	}

	void formatter::insert_pattern_data(std::initializer_list<pattern_attribute_t> pattern_data)
	{
		for (const auto& [verbose, shortened, attribute] : pattern_data)
		{
			m_pattern_data.insert_or_assign({ verbose, shortened }, attribute);
		}
	}

	std::unordered_map<duplex, std::string> formatter::m_pattern_data = formatter_data::pattern_data;
	std::unordered_map<std::string_view, std::string_view> formatter::m_color_data = formatter_data::color_data;
}