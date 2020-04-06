#pragma once

#include <string>

namespace lwlog::details::color
{
	constexpr std::string_view reset()		{ return "\u001b[0m"; }
	constexpr std::string_view bold()		{ return "\u001b[1m"; }
	constexpr std::string_view underlined()	{ return "\u001b[4m"; }
	constexpr std::string_view reversed()	{ return "\u001b[7m"; }

	constexpr std::string_view foreground_black()	{ return "\u001b[30m"; }
	constexpr std::string_view foreground_red()		{ return "\u001b[31m"; }
	constexpr std::string_view foreground_green()	{ return "\u001b[32m"; }
	constexpr std::string_view foreground_yellow()	{ return "\u001b[33m"; }
	constexpr std::string_view foreground_blue()	{ return "\u001b[34m"; }
	constexpr std::string_view foreground_magenta()	{ return "\u001b[35m"; }
	constexpr std::string_view foreground_cyan()	{ return "\u001b[36m"; }
	constexpr std::string_view foreground_white()	{ return "\u001b[37m"; }

	constexpr std::string_view foreground_bright_black()	{ return "\u001b[30;1m"; }
	constexpr std::string_view foreground_bright_red()		{ return "\u001b[31;1m"; }
	constexpr std::string_view foreground_bright_green()	{ return "\u001b[32;1m"; }
	constexpr std::string_view foreground_bright_yellow()	{ return "\u001b[33;1m"; }
	constexpr std::string_view foreground_bright_blue()		{ return "\u001b[34;1m"; }
	constexpr std::string_view foreground_bright_magenta()	{ return "\u001b[35;1m"; }
	constexpr std::string_view foreground_bright_cyan()		{ return "\u001b[36;1m"; }
	constexpr std::string_view foreground_bright_white()	{ return "\u001b[37;1m"; }

	constexpr std::string_view background_black()	{ return "\u001b[40m"; }
	constexpr std::string_view background_red()		{ return "\u001b[41m"; }
	constexpr std::string_view background_green()	{ return "\u001b[42m"; }
	constexpr std::string_view background_yellow()	{ return "\u001b[43m"; }
	constexpr std::string_view background_blue()	{ return "\u001b[44m"; }
	constexpr std::string_view background_magenta()	{ return "\u001b[45m"; }
	constexpr std::string_view background_cyan()	{ return "\u001b[46m"; }
	constexpr std::string_view background_white()	{ return "\u001b[47m"; }

	constexpr std::string_view background_bright_black()	{ return "\u001b[40;1m"; }
	constexpr std::string_view background_bright_red()		{ return "\u001b[41;1m"; }
	constexpr std::string_view background_bright_green()	{ return "\u001b[42;1m"; }
	constexpr std::string_view background_bright_yellow()	{ return "\u001b[43;1m"; }
	constexpr std::string_view background_bright_blue()		{ return "\u001b[44;1m"; }
	constexpr std::string_view background_bright_magenta()	{ return "\u001b[45;1m"; }
	constexpr std::string_view background_bright_cyan()		{ return "\u001b[46;1m"; }
	constexpr std::string_view background_bright_white()	{ return "\u001b[47;1m"; }
}