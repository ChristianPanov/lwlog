#pragma once

#include <cstdint>
#include <type_traits>

#include "tweakme.h"

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
		all			=	(1 << 6)
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

	constexpr const char* to_string(level t_level)
	{
		switch (t_level)
		{
		case level::info:		return "info";
		case level::warning:	return "warning";
		case level::error:		return "error";
		case level::critical:	return "critical";
		case level::debug:		return "debug";
		}
	}

	constexpr const char* color_value(level t_level)
	{
		switch (t_level)
		{
		case level::info:		return "\u001b[30;1m";
		case level::warning:	return "\u001b[33;1m";
		case level::error:		return "\u001b[31;1m";
		case level::critical:	return "\u001b[41;1m";
		case level::debug:		return "\u001b[37;1m";
		}
	}
}