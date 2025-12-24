#pragma once

#include <cstdint>
#include <type_traits>

namespace lwlog
{
	enum class level : std::uint8_t
	{
		none		=	(1 << 0),
		info		=	(1 << 1),
		warning		=	(1 << 2),
		error		=	(1 << 3),
		critical	=	(1 << 4),
		debug		=	(1 << 5),
		trace		=	(1 << 6),
		all			=	(1 << 7)
	};

	constexpr level operator|(level lhs, level rhs)
	{
		return static_cast<level>(
			static_cast<std::underlying_type_t<level>>(lhs) |
			static_cast<std::underlying_type_t<level>>(rhs)
			);
	}

	constexpr level operator&(level lhs, level rhs)
	{
		return static_cast<level>(
			static_cast<std::underlying_type_t<level>>(lhs) &
			static_cast<std::underlying_type_t<level>>(rhs)
			);
	}
}

namespace lwlog::level_details
{
	constexpr bool has_level(level lhs, level rhs)
	{
		return static_cast<std::underlying_type_t<level>>(lhs) &
			static_cast<std::underlying_type_t<level>>(rhs);
	}

	constexpr std::string_view to_string(level log_level)
	{
		switch (log_level)
		{
		case level::info:		return "info";
		case level::warning:	return "warning";
		case level::error:		return "error";
		case level::critical:	return "critical";
		case level::debug:		return "debug";
		case level::trace:		return "trace";
		case level::all: 		return {};
		case level::none:		return {};
		}
	}

	constexpr std::string_view to_color(level log_level)
	{
		switch (log_level)
		{
		case level::info:     return "\x1b[37m";
		case level::warning:  return "\x1b[93m";
		case level::error:    return "\x1b[91m";
		case level::critical: return "\x1b[1;97;101m";
		case level::debug:    return "\x1b[97m";
		case level::trace:    return "\x1b[97m";
		default: return {};
		}
    }
}