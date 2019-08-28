#include "formatter.h"
#include "datetime.h"
#include "utilities.h"

namespace lwlog
{
	std::vector<details::Key_Value> formatter::m_inserted_patternData_keys = {};

	std::unordered_map<details::Key_Value, std::string> formatter::m_patternData =
	{
		{{"%seconds%",			"%s"}, lwlog::datetime::get_second()},
		{{"%minute%",			"%i"}, lwlog::datetime::get_minute()},
		{{"%hour_24%",			"%H"}, lwlog::datetime::get_hour_24()},
		{{"%hour_12%",			"%h"}, lwlog::datetime::get_hour_12()},
		{{"%day%",				"%M"}, lwlog::datetime::get_day()},
		{{"%weekday_abr%",		"%A"}, lwlog::datetime::get_weekday_abbreviated()},
		{{"%weekday%",			"%a"}, lwlog::datetime::get_weekday()},
		{{"%month%",			"%m"}, lwlog::datetime::get_month()},
		{{"%mont_name_abr%",	"%B"}, lwlog::datetime::get_month_name_abbreviated()},
		{{"%month_name%",		"%b"}, lwlog::datetime::get_month_name()},
		{{"%year_short%",		"%C"}, lwlog::datetime::get_year_short()},
		{{"%year%",				"%c"}, lwlog::datetime::get_year()},
		{{"%date_short%",		"%D"}, lwlog::datetime::get_date_short()},
		{{"%date%",				"%d"}, lwlog::datetime::get_date()},
		{{"%time%",				"%x"}, lwlog::datetime::get_time()}
	};

	void formatter::insert_pattern_data(details::Key_Value key, std::string_view value)
	{
		m_inserted_patternData_keys.emplace_back(key);
		m_patternData.emplace(key, value);
	}

	std::string formatter::format(std::string pattern)
	{
		for (auto const& [key, value] : m_patternData)
		{
			auto [verbose, shortened] = key;
			details::replace_in_string(pattern, verbose, value);
		}

		for (auto const& [key, value] : m_patternData)
		{
			auto [verbose, shortened] = key;
			details::replace_in_string(pattern, shortened, value);
		}

		for (auto& i : m_inserted_patternData_keys)
		{
			m_patternData.erase(i);
		}

		return pattern;
	}
}
