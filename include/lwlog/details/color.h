#pragma once

#include <string>

namespace lwlog::details::color
{
	constexpr const char* reset()		{ return "\u001b[0m"; }
	constexpr const char* bold()		{ return "\u001b[1m"; }
	constexpr const char* underlined()	{ return "\u001b[4m"; }
	constexpr const char* reversed()	{ return "\u001b[7m"; }

	constexpr const char* foreground_black()	{ return "\u001b[30m"; }
	constexpr const char* foreground_red()		{ return "\u001b[31m"; }
	constexpr const char* foreground_green()	{ return "\u001b[32m"; }
	constexpr const char* foreground_yellow()	{ return "\u001b[33m"; }
	constexpr const char* foreground_blue()		{ return "\u001b[34m"; }
	constexpr const char* foreground_magenta()	{ return "\u001b[35m"; }
	constexpr const char* foreground_cyan()		{ return "\u001b[36m"; }
	constexpr const char* foreground_white()	{ return "\u001b[37m"; }

	constexpr const char* foreground_bright_black()		{ return "\u001b[30;1m"; }
	constexpr const char* foreground_bright_red()		{ return "\u001b[31;1m"; }
	constexpr const char* foreground_bright_green()		{ return "\u001b[32;1m"; }
	constexpr const char* foreground_bright_yellow()	{ return "\u001b[33;1m"; }
	constexpr const char* foreground_bright_blue()		{ return "\u001b[34;1m"; }
	constexpr const char* foreground_bright_magenta()	{ return "\u001b[35;1m"; }
	constexpr const char* foreground_bright_cyan()		{ return "\u001b[36;1m"; }
	constexpr const char* foreground_bright_white()		{ return "\u001b[37;1m"; }

	constexpr const char* background_black()	{ return "\u001b[40m"; }
	constexpr const char* background_red()		{ return "\u001b[41m"; }
	constexpr const char* background_green()	{ return "\u001b[42m"; }
	constexpr const char* background_yellow()	{ return "\u001b[43m"; }
	constexpr const char* background_blue()		{ return "\u001b[44m"; }
	constexpr const char* background_magenta()	{ return "\u001b[45m"; }
	constexpr const char* background_cyan()		{ return "\u001b[46m"; }
	constexpr const char* background_white()	{ return "\u001b[47m"; }

	constexpr const char* background_bright_black()		{ return "\u001b[40;1m"; }
	constexpr const char* background_bright_red()		{ return "\u001b[41;1m"; }
	constexpr const char* background_bright_green()		{ return "\u001b[42;1m"; }
	constexpr const char* background_bright_yellow()	{ return "\u001b[43;1m"; }
	constexpr const char* background_bright_blue()		{ return "\u001b[44;1m"; }
	constexpr const char* background_bright_magenta()	{ return "\u001b[45;1m"; }
	constexpr const char* background_bright_cyan()		{ return "\u001b[46;1m"; }
	constexpr const char* background_bright_white()		{ return "\u001b[47;1m"; }
}
