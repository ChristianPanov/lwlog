#pragma once

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
		case level::info:		return LWLOG_INFO_STR;
		case level::warning:	return LWLOG_WARNING_STR;
		case level::error:		return LWLOG_ERROR_STR;
		case level::critical:	return LWLOG_CRITICAL_STR;
		case level::debug:		return LWLOG_DEBUG_STR;
		}
	}

	constexpr const char* color_value(level t_level)
	{
		switch (t_level)
		{
		case level::info:		return LWLOG_INFO_COLOR;
		case level::warning:	return LWLOG_WARNING_COLOR;
		case level::error:		return LWLOG_ERROR_COLOR;
		case level::critical:	return LWLOG_CRITICAL_COLOR;
		case level::debug:		return LWLOG_DEBUG_COLOR;
		}
	}
}