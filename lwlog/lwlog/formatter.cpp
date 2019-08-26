#include "formatter.h"
#include "details.h"
#include "datetime.h"

namespace lwlog
{
	std::regex formatter::m_pattern_regex("(\\%\\w{1})");

	std::vector<std::string> formatter::m_inserted_patternData_keys = {};

	std::unordered_map<std::string, std::string> formatter::m_patternData =
	{
		{"%s", lwlog::datetime::get_second()},
		{"%i", lwlog::datetime::get_minute()},
		{"%H", lwlog::datetime::get_hour_24()},
		{"%h", lwlog::datetime::get_hour_12()},
		{"%M", lwlog::datetime::get_day()},
		{"%A", lwlog::datetime::get_weekday_abbreviated()},
		{"%a", lwlog::datetime::get_weekday()},
		{"%m", lwlog::datetime::get_month()},
		{"%B", lwlog::datetime::get_month_name_abbreviated()},
		{"%b", lwlog::datetime::get_month_name()},
		{"%C", lwlog::datetime::get_year_short()},
		{"%c", lwlog::datetime::get_year()},
		{"%D", lwlog::datetime::get_date_short()},
		{"%d", lwlog::datetime::get_date()},
		{"%x", lwlog::datetime::get_time()}
	};

	void formatter::insert_pattern_data(std::string_view key, std::string_view value)
	{
		m_inserted_patternData_keys.emplace_back(key);
		m_patternData.emplace(key, value);
	}

	std::string formatter::format(std::string_view message, std::string pattern, std::regex reg)
	{
		std::vector<std::string> pattern_string_tokens;

		details::populate_vec_with_regex_matches_from_str(pattern_string_tokens, reg, pattern);

		for (int i = 0; i < pattern_string_tokens.size(); ++i)
		{
			for (auto it = m_patternData.begin(); it != m_patternData.end(); ++it)
			{
				if (pattern_string_tokens[i] == it->first)
				{
					details::replace_in_string(pattern, pattern_string_tokens[i], it->second);
				}
			}
		}

		for (auto i : m_inserted_patternData_keys)
		{
			m_patternData.erase(i);
		}

		return pattern;
	}
}
