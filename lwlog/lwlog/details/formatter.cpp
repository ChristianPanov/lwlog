#include "formatter.h"
#include "datetime.h"
#include "color.h"
#include "utilities.h"

namespace lwlog::details
{
	std::unordered_map<duplex<std::string, std::string>, std::string> formatter::m_pattern_data =
	{
		{{"{seconds}",			"%s"}, datetime::get_second()},
		{{"{minute}",			"%i"}, datetime::get_minute()},
		{{"{hour_24}",			"%H"}, datetime::get_hour_24()},
		{{"{hour_12}",			"%h"}, datetime::get_hour_12()},
		{{"{day}",				"%M"}, datetime::get_day()},
		{{"{weekday_abr}",		"%A"}, datetime::get_weekday_abbreviated()},
		{{"{weekday}",			"%a"}, datetime::get_weekday()},
		{{"{month}",			"%m"}, datetime::get_month()},
		{{"{mont_name_abr}",	"%B"}, datetime::get_month_name_abbreviated()},
		{{"{month_name}",		"%b"}, datetime::get_month_name()},
		{{"{year_short}",		"%C"}, datetime::get_year_short()},
		{{"{year}",				"%c"}, datetime::get_year()},
		{{"{date_short}",		"%D"}, datetime::get_date_short()},
		{{"{date}",				"%d"}, datetime::get_date()},
		{{"{time}",				"%x"}, datetime::get_time()},

		{{						"%%"}, "%"},
		{{						"{{"}, "{"},
		{{						"}}"}, "}"}
	};

	std::unordered_map<std::string, std::string> formatter::m_color_data =
	{
		{"^black^",			color::foreground_black()},
		{"^red^",			color::foreground_red()},
		{"^green^",			color::foreground_green()},
		{"^yellow^",		color::foreground_yellow()},
		{"^blue^",			color::foreground_blue()},
		{"^magenta^",		color::foreground_magenta()},
		{"^cyan^",			color::foreground_cyan()},
		{"^white^",			color::foreground_white()},

		{"^br_black^",		color::foreground_bright_black()},
		{"^br_red^",		color::foreground_bright_red()},
		{"^br_green^",		color::foreground_bright_green()},
		{"^br_yellow^",		color::foreground_bright_yellow()},
		{"^br_blue^",		color::foreground_bright_blue()},
		{"^br_magenta^",	color::foreground_bright_magenta()},
		{"^br_cyan^",		color::foreground_bright_cyan()},
		{"^br_white^",		color::foreground_bright_white()},

		{"^bg_black^",		color::background_black()},
		{"^bg_red^",		color::background_red()},
		{"^bg_green^",		color::background_green()},
		{"^bg_yellow^",		color::background_yellow()},
		{"^bg_blue^",		color::background_blue()},
		{"^bg_magenta^",	color::background_magenta()},
		{"^bg_cyan^",		color::background_cyan()},
		{"^bg_white^",		color::background_white()},

		{"^bg_br_black^",	color::background_bright_black()},
		{"^bg_br_red^",		color::background_bright_red()},
		{"^bg_br_green^",	color::background_bright_green()},
		{"^bg_br_yellow^",	color::background_bright_yellow()},
		{"^bg_br_blue^",	color::background_bright_blue()},
		{"^bg_br_magenta^", color::background_bright_magenta()},
		{"^bg_br_cyan^",	color::background_bright_cyan()},
		{"^bg_br_white^",	color::background_bright_white()},

		{"^reset^",			color::reset()},
		{"^bold^",			color::bold()},
		{"^underlined^",	color::underlined()},
		{"^reversed^",		color::reversed()},

		{{					"^^"}, "^"}
	};

	std::string formatter::format(std::string pattern, bool should_color)
	{
		for (const auto& [key, value] : m_pattern_data)
		{
			const auto& [verbose, shortened] = key;
			if (!verbose.empty())
			{
				utilities::replace_in_string(pattern, verbose, value);
			}
		}

		for (const auto& [key, value] : m_pattern_data)
		{
			const auto& [verbose, shortened] = key;
			if (!shortened.empty())
			{
				utilities::replace_in_string(pattern, shortened, value);
			}
		}

		for (const auto& [key, value] : m_color_data)
		{
			utilities::replace_in_string(pattern, key, (should_color == true ? value : ""));
		}

		return pattern;
	}

	void formatter::insert_pattern_data(std::initializer_list<duplex<duplex<std::string, std::string>, 
		std::string>> pattern_data)
	{
		for (const auto& [duplex_key, value] : pattern_data)
		{
			m_pattern_data.insert_or_assign(duplex_key, value);
		}
	}
}
