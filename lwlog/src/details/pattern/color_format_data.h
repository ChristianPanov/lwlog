#pragma once

namespace lwlog::details
{
	static const std::unordered_map<std::string_view, std::string_view> color_data =
	{
		{".black(",			"\u001b[30m"},
		{".red(",			"\u001b[31m"},
		{".green(",			"\u001b[32m"},
		{".yellow(",		"\u001b[33m"},
		{".blue(",			"\u001b[34m"},
		{".magenta(",		"\u001b[35m"},
		{".cyan(",			"\u001b[36m"},
		{".white(",			"\u001b[37m"},

		{".br_black(",		"\u001b[30;1m"},
		{".br_red(",		"\u001b[31;1m"},
		{".br_green(",		"\u001b[32;1m"},
		{".br_yellow(",		"\u001b[33;1m"},
		{".br_blue(",		"\u001b[34;1m"},
		{".br_magenta(",	"\u001b[35;1m"},
		{".br_cyan(",		"\u001b[36;1m"},
		{".br_white(",		"\u001b[37;1m"},

		{".bg_black(",		"\u001b[40m"},
		{".bg_red(",		"\u001b[41m"},
		{".bg_green(",		"\u001b[42m"},
		{".bg_yellow(",		"\u001b[43m"},
		{".bg_blue(",		"\u001b[44m"},
		{".bg_magenta(",	"\u001b[45m"},
		{".bg_cyan(",		"\u001b[46m"},
		{".bg_white(",		"\u001b[47m"},

		{".br_bg_black(",	"\u001b[40;1m"},
		{".br_bg_red(",		"\u001b[41;1m"},
		{".br_bg_green(",	"\u001b[42;1m"},
		{".br_bg_yellow(",	"\u001b[43;1m"},
		{".br_bg_blue(",	"\u001b[44;1m"},
		{".br_bg_magenta(", "\u001b[45;1m"},
		{".br_bg_cyan(",	"\u001b[46;1m"},
		{".br_bg_white(",	"\u001b[47;1m"}
	};
}