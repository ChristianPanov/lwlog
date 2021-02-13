#pragma once

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

	static level operator|(level lhs, level rhs)
	{
		return static_cast<level>(
			static_cast<std::underlying_type_t<level>>(lhs) |
			static_cast<std::underlying_type_t<level>>(rhs)
			);
	}

	static level operator&(level lhs, level rhs)
	{
		return static_cast<level>(
			static_cast<std::underlying_type_t<level>>(lhs) &
			static_cast<std::underlying_type_t<level>>(rhs)
			);
	}
}

namespace lwlog::level_details
{
	constexpr std::underlying_type_t<level> value(level t_level)
	{
		return static_cast<std::underlying_type_t<level>>(t_level);
	}

	constexpr const char* to_string(level level)
	{
		switch (level)
		{
		case level::info:		return "info";		break;
		case level::warning:	return "warning";	break;
		case level::error:		return "error";		break;
		case level::critical:	return "critical";	break;
		case level::debug:		return "debug";		break;
		}
	}

	constexpr const char* color_value(level level)
	{
		switch (level)
		{
		case level::info:		return "\u001b[30;1m";  break;
		case level::warning:	return "\u001b[33;1m";  break;
		case level::error:		return "\u001b[31;1m";  break;
		case level::critical:	return "\u001b[41;1m";  break;
		case level::debug:		return "\u001b[37;1m";  break;
		}
	}
}