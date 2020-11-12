#pragma once

#include "datetime.h"
#include "color.h"

namespace lwlog::details::formatter_data
{
	static std::unordered_map<duplex, std::string> pattern_data =
	{
		{{"{seconds}",			"%S"}, datetime::get_second()},
		{{"{minute}",			"%M"}, datetime::get_minute()},
		{{"{hour_24}",			"%H"}, datetime::get_hour_24()},
		{{"{hour_12}",			"%I"}, datetime::get_hour_12()},
		{{"{ampm}",				"%p"}, datetime::get_ampm()},
		{{"{12_clock}",			"%r"}, datetime::get_12_hour_clock()},
		{{"{24_clock}",			"%R"}, datetime::get_24_hour_clock()},
		{{"{day}",				"%d"}, datetime::get_day()},
		{{"{weekday_abr}",		"%a"}, datetime::get_weekday_abbreviated()},
		{{"{weekday}",			"%A"}, datetime::get_weekday()},
		{{"{month}",			"%m"}, datetime::get_month()},
		{{"{mont_name_abr}",	"%b"}, datetime::get_month_name_abbreviated()},
		{{"{month_name}",		"%B"}, datetime::get_month_name()},
		{{"{year_short}",		"%y"}, datetime::get_year_short()},
		{{"{year}",				"%Y"}, datetime::get_year()},
		{{"{date_short}",		"%D"}, datetime::get_date_short()},
		{{"{date}",				"%F"}, datetime::get_date()},
		{{"{time}",				"%T"}, datetime::get_time()},

		{{						"%%"}, "%"},
		{{						"{{"}, "{"},
		{{						"}}"}, "}"}
	};

	static std::unordered_map<std::string_view, std::string_view> color_data =
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
}