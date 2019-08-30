#pragma once

#include <string>

namespace lwlog::color
{
	inline constexpr std::string_view reset()		{ return "\u001b[0m"; }
	inline constexpr std::string_view bold()		{ return "\u001b[1m"; }
	inline constexpr std::string_view underlined()	{ return "\u001b[4m"; }
	inline constexpr std::string_view reversed()	{ return "\u001b[7m"; }

	inline constexpr std::string_view foreground_black()	{ return "\u001b[30m"; }
	inline constexpr std::string_view foreground_red()		{ return "\u001b[31m"; }
	inline constexpr std::string_view foreground_green()	{ return "\u001b[32m"; }
	inline constexpr std::string_view foreground_yellow()	{ return "\u001b[33m"; }
	inline constexpr std::string_view foreground_blue()		{ return "\u001b[34m"; }
	inline constexpr std::string_view foreground_magenta()	{ return "\u001b[35m"; }
	inline constexpr std::string_view foreground_cyan()		{ return "\u001b[36m"; }
	inline constexpr std::string_view foreground_white()	{ return "\u001b[37m"; }

	inline constexpr std::string_view foreground_bright_black()		{ return "\u001b[30;1m"; }
	inline constexpr std::string_view foreground_bright_red()		{ return "\u001b[31;1m"; }
	inline constexpr std::string_view foreground_bright_green()		{ return "\u001b[32;1m"; }
	inline constexpr std::string_view foreground_bright_yellow()	{ return "\u001b[33;1m"; }
	inline constexpr std::string_view foreground_bright_blue()		{ return "\u001b[34;1m"; }
	inline constexpr std::string_view foreground_bright_magenta()	{ return "\u001b[35;1m"; }
	inline constexpr std::string_view foreground_bright_cyan()		{ return "\u001b[36;1m"; }
	inline constexpr std::string_view foreground_bright_white()		{ return "\u001b[37;1m"; }

	inline constexpr std::string_view background_black()	{ return "\u001b[40m"; }
	inline constexpr std::string_view background_red()		{ return "\u001b[41m"; }
	inline constexpr std::string_view background_green()	{ return "\u001b[42m"; }
	inline constexpr std::string_view background_yellow()	{ return "\u001b[43m"; }
	inline constexpr std::string_view background_blue()		{ return "\u001b[44m"; }
	inline constexpr std::string_view background_magenta()	{ return "\u001b[45m"; }
	inline constexpr std::string_view background_cyan()		{ return "\u001b[46m"; }
	inline constexpr std::string_view background_white()	{ return "\u001b[47m"; }

	inline constexpr std::string_view background_bright_black()		{ return "\u001b[40;1m"; }
	inline constexpr std::string_view background_bright_red()		{ return "\u001b[41;1m"; }
	inline constexpr std::string_view background_bright_green()		{ return "\u001b[42;1m"; }
	inline constexpr std::string_view background_bright_yellow()	{ return "\u001b[43;1m"; }
	inline constexpr std::string_view background_bright_blue()		{ return "\u001b[44;1m"; }
	inline constexpr std::string_view background_bright_magenta()	{ return "\u001b[45;1m"; }
	inline constexpr std::string_view background_bright_cyan()		{ return "\u001b[46;1m"; }
	inline constexpr std::string_view background_bright_white()		{ return "\u001b[47;1m"; }
}