#pragma once

#include "details/color.h"

namespace lwlog::details
{
	static std::unordered_map<std::string_view, std::string_view> color_data =
	{
		{")",				color::reset()},

		{".black(",			color::foreground_black()},
		{".red(",			color::foreground_red()},
		{".green(",			color::foreground_green()},
		{".yellow(",		color::foreground_yellow()},
		{".blue(",			color::foreground_blue()},
		{".magenta(",		color::foreground_magenta()},
		{".cyan(",			color::foreground_cyan()},
		{".white(",			color::foreground_white()},

		{".br_black(",		color::foreground_bright_black()},
		{".br_red(",		color::foreground_bright_red()},
		{".br_green(",		color::foreground_bright_green()},
		{".br_yellow(",		color::foreground_bright_yellow()},
		{".br_blue(",		color::foreground_bright_blue()},
		{".br_magenta(",	color::foreground_bright_magenta()},
		{".br_cyan(",		color::foreground_bright_cyan()},
		{".br_white(",		color::foreground_bright_white()},

		{".bg_black(",		color::background_black()},
		{".bg_red(",		color::background_red()},
		{".bg_green(",		color::background_green()},
		{".bg_yellow(",		color::background_yellow()},
		{".bg_blue(",		color::background_blue()},
		{".bg_magenta(",	color::background_magenta()},
		{".bg_cyan(",		color::background_cyan()},
		{".bg_white(",		color::background_white()},

		{".br_bg_black(",	color::background_bright_black()},
		{".br_bg_red(",		color::background_bright_red()},
		{".br_bg_green(",	color::background_bright_green()},
		{".br_bg_yellow(",	color::background_bright_yellow()},
		{".br_bg_blue(",	color::background_bright_blue()},
		{".br_bg_magenta(", color::background_bright_magenta()},
		{".br_bg_cyan(",	color::background_bright_cyan()},
		{".br_bg_white(",	color::background_bright_white()}
	};
}