#pragma once

#include <string>

namespace lwlog::details::color
{
	inline std::string reset()		{ return "\u001b[0m"; }
	inline std::string bold()		{ return "\u001b[1m"; }
	inline std::string underlined()	{ return "\u001b[4m"; }
	inline std::string reversed()	{ return "\u001b[7m"; }

	inline std::string foreground_black()	{ return "\u001b[30m"; }
	inline std::string foreground_red()		{ return "\u001b[31m"; }
	inline std::string foreground_green()	{ return "\u001b[32m"; }
	inline std::string foreground_yellow()	{ return "\u001b[33m"; }
	inline std::string foreground_blue()	{ return "\u001b[34m"; }
	inline std::string foreground_magenta()	{ return "\u001b[35m"; }
	inline std::string foreground_cyan()	{ return "\u001b[36m"; }
	inline std::string foreground_white()	{ return "\u001b[37m"; }

	inline std::string foreground_bright_black()	{ return "\u001b[30;1m"; }
	inline std::string foreground_bright_red()		{ return "\u001b[31;1m"; }
	inline std::string foreground_bright_green()	{ return "\u001b[32;1m"; }
	inline std::string foreground_bright_yellow()	{ return "\u001b[33;1m"; }
	inline std::string foreground_bright_blue()		{ return "\u001b[34;1m"; }
	inline std::string foreground_bright_magenta()	{ return "\u001b[35;1m"; }
	inline std::string foreground_bright_cyan()		{ return "\u001b[36;1m"; }
	inline std::string foreground_bright_white()	{ return "\u001b[37;1m"; }

	inline std::string background_black()	{ return "\u001b[40m"; }
	inline std::string background_red()		{ return "\u001b[41m"; }
	inline std::string background_green()	{ return "\u001b[42m"; }
	inline std::string background_yellow()	{ return "\u001b[43m"; }
	inline std::string background_blue()	{ return "\u001b[44m"; }
	inline std::string background_magenta()	{ return "\u001b[45m"; }
	inline std::string background_cyan()	{ return "\u001b[46m"; }
	inline std::string background_white()	{ return "\u001b[47m"; }

	inline std::string background_bright_black()	{ return "\u001b[40;1m"; }
	inline std::string background_bright_red()		{ return "\u001b[41;1m"; }
	inline std::string background_bright_green()	{ return "\u001b[42;1m"; }
	inline std::string background_bright_yellow()	{ return "\u001b[43;1m"; }
	inline std::string background_bright_blue()		{ return "\u001b[44;1m"; }
	inline std::string background_bright_magenta()	{ return "\u001b[45;1m"; }
	inline std::string background_bright_cyan()		{ return "\u001b[46;1m"; }
	inline std::string background_bright_white()	{ return "\u001b[47;1m"; }
}