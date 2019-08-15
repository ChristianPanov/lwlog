#include "formatter.h"

void formatter::update_pattern_data(std::string_view key, std::string_view value)
{
	m_patternData.emplace(key, value);
}

std::string formatter::format(std::string_view message, std::string pattern)
{
	std::vector<std::string> pattern_string_tokens;

	detail::populate_vec_with_regex_matches_from_str(pattern_string_tokens, pattern_regex, pattern);

	for (int i = 0; i < pattern_string_tokens.size(); ++i)
	{
		for (auto it = m_patternData.begin(); it != m_patternData.end(); ++it)
		{
			if (pattern_string_tokens[i] == it->first)
			{
				detail::replace_in_string(pattern, pattern_string_tokens[i], it->second);
			}
		}
	}

	return pattern;
}
