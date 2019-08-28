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
		{{"%time%",				"%x"}, lwlog::datetime::get_time()},

		{{"^black^"	},			"\u001b[30m"},
		{{"^red^"},				"\u001b[31m"},
		{{"^green^"},			"\u001b[32m"},
		{{"^yellow^"},			"\u001b[33m"},
		{{"^blue^"},			"\u001b[34m"},
		{{"^magenta^"},			"\u001b[35m"},
		{{"^cyan^"},			"\u001b[36m"},
		{{"^white^"},			"\u001b[37m"},

		{{"^br_black^"},		"\u001b[30;1m"},
		{{"^br_red^"},			"\u001b[31;1m"},
		{{"^br_green^"},		"\u001b[32;1m"},
		{{"^br_yellow^"},		"\u001b[33;1m"},
		{{"^br_blue^"},			"\u001b[34;1m"},
		{{"^br_magenta^"},		"\u001b[35;1m"},
		{{"^br_cyan^"},			"\u001b[36;1m"},
		{{"^br_white^"},		"\u001b[37;1m"},

		{{"^bg_black^"},		"\u001b[40m"},
		{{"^bg_red^"},			"\u001b[41m"},
		{{"^bg_green^"},		"\u001b[42m"},
		{{"^bg_yellow^"},		"\u001b[43m"},
		{{"^bg_blue^"},			"\u001b[44m"},
		{{"^bg_magenta^"},		"\u001b[45m"},
		{{"^bg_cyan^"},			"\u001b[46m"},
		{{"^bg_white^"},		"\u001b[47m"},

		{{"^bg_br_black^"},		"\u001b[40;1m"},
		{{"^bg_br_red^"},		"\u001b[41;1m"},
		{{"^bg_br_green^"},		"\u001b[42;1m"},
		{{"^bg_br_yellow^"},	"\u001b[43;1m"},
		{{"^bg_br_blue^"},		"\u001b[44;1m"},
		{{"^bg_br_magenta^"},	"\u001b[45;1m"},
		{{"^bg_br_cyan^"},		"\u001b[46;1m"},
		{{"^bg_br_white^"},		"\u001b[47;1m"},

		{{"^reset^"},			"\u001b[0m"},
		{{"^bold^"},			"\u001b[1m"},
		{{"^underlined^"},		"\u001b[4m"},
		{{"^reversed^"},		"\u001b[7m"},
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
			if (!verbose.empty())
			{
				details::replace_in_string(pattern, verbose, value);
			}
		}

		for (auto const& [key, value] : m_patternData)
		{
			auto [verbose, shortened] = key;
			if (!shortened.empty())
			{
				details::replace_in_string(pattern, shortened, value);
			}
		}

		for (auto& i : m_inserted_patternData_keys)
		{
			m_patternData.erase(i);
		}

		return pattern;
	}
}
