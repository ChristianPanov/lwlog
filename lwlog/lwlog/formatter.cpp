#include "formatter.h"
#include "datetime.h"
#include "color.h"
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
		{{"%day%",			"%M"}, lwlog::datetime::get_day()},
		{{"%weekday_abr%",		"%A"}, lwlog::datetime::get_weekday_abbreviated()},
		{{"%weekday%",			"%a"}, lwlog::datetime::get_weekday()},
		{{"%month%",			"%m"}, lwlog::datetime::get_month()},
		{{"%mont_name_abr%",		"%B"}, lwlog::datetime::get_month_name_abbreviated()},
		{{"%month_name%",		"%b"}, lwlog::datetime::get_month_name()},
		{{"%year_short%",		"%C"}, lwlog::datetime::get_year_short()},
		{{"%year%",			"%c"}, lwlog::datetime::get_year()},
		{{"%date_short%",		"%D"}, lwlog::datetime::get_date_short()},
		{{"%date%",			"%d"}, lwlog::datetime::get_date()},
		{{"%time%",			"%x"}, lwlog::datetime::get_time()},

		{{"^black^"			}, lwlog::color::foreground_black()},
		{{"^red^"			}, lwlog::color::foreground_red()},
		{{"^green^"			}, lwlog::color::foreground_green()},
		{{"^yellow^"			}, lwlog::color::foreground_yellow()},
		{{"^blue^"			}, lwlog::color::foreground_blue()},
		{{"^magenta^"			}, lwlog::color::foreground_magenta()},
		{{"^cyan^"			}, lwlog::color::foreground_cyan()},
		{{"^white^"			}, lwlog::color::foreground_white()},

		{{"^br_black^"			}, lwlog::color::foreground_bright_black()},
		{{"^br_red^"			}, lwlog::color::foreground_bright_red()},
		{{"^br_green^"			}, lwlog::color::foreground_bright_green()},
		{{"^br_yellow^"			}, lwlog::color::foreground_bright_yellow()},
		{{"^br_blue^"			}, lwlog::color::foreground_bright_blue()},
		{{"^br_magenta^"		}, lwlog::color::foreground_bright_magenta()},
		{{"^br_cyan^"			}, lwlog::color::foreground_bright_cyan()},
		{{"^br_white^"			}, lwlog::color::foreground_bright_white()},

		{{"^bg_black^"			}, lwlog::color::background_black()},
		{{"^bg_red^"			}, lwlog::color::background_red()},
		{{"^bg_green^"			}, lwlog::color::background_green()},
		{{"^bg_yellow^"			}, lwlog::color::background_yellow()},
		{{"^bg_blue^"			}, lwlog::color::background_blue()},
		{{"^bg_magenta^"		}, lwlog::color::background_magenta()},
		{{"^bg_cyan^"			}, lwlog::color::background_cyan()},
		{{"^bg_white^"			}, lwlog::color::background_white()},

		{{"^bg_br_black^"		}, lwlog::color::background_bright_black()},
		{{"^bg_br_red^"			}, lwlog::color::background_bright_red()},
		{{"^bg_br_green^"		}, lwlog::color::background_bright_green()},
		{{"^bg_br_yellow^"		}, lwlog::color::background_bright_yellow()},
		{{"^bg_br_blue^"		}, lwlog::color::background_bright_blue()},
		{{"^bg_br_magenta^"		}, lwlog::color::background_bright_magenta()},
		{{"^bg_br_cyan^"		}, lwlog::color::background_bright_cyan()},
		{{"^bg_br_white^"		}, lwlog::color::background_bright_white()},

		{{"^reset^"			}, lwlog::color::reset()},
		{{"^bold^"			}, lwlog::color::bold()},
		{{"^underlined^"		}, lwlog::color::underlined()},
		{{"^reversed^"			}, lwlog::color::reversed()},

		{{				"%%"}, "%"},
		{{				"^^"}, "^"}
	};

	void formatter::insert_pattern_data(details::Key_Value key, std::string value)
	{
		m_inserted_patternData_keys.emplace_back(key);
		m_patternData.emplace(key, value);
	}

	std::string formatter::format(std::string pattern)
	{
		for (auto const& [key, value] : m_patternData)
		{
			auto& [verbose, shortened] = key;
			if (!verbose.empty())
			{
				details::replace_in_string(pattern, verbose, value);
			}
		}

		for (auto const& [key, value] : m_patternData)
		{
			auto& [verbose, shortened] = key;
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
