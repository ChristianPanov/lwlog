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

	constexpr const char* to_string(level log_level)
	{
		switch (log_level)
		{
		case level::info:		return "info";
		case level::warning:	return "warning";
		case level::error:		return "error";
		case level::critical:	return "critical";
		case level::debug:		return "debug";
		}
	}
}