#pragma once

namespace lwlog
{
	enum class level_t : std::uint8_t
	{
		none		=	(1 << 0),
		info		=	(1 << 1),
		warning		=	(1 << 2),
		error		=	(1 << 3),
		critical	=	(1 << 4),
		debug		=	(1 << 5),
		all			=	(1 << 6)
	};

	static level_t operator|(level_t lhs, level_t rhs)
	{
		return static_cast<level_t>(
			static_cast<std::underlying_type_t<level_t>>(lhs) | 
			static_cast<std::underlying_type_t<level_t>>(rhs)
			);
	}

	static level_t operator&(level_t lhs, level_t rhs)
	{
		return static_cast<level_t>(
			static_cast<std::underlying_type_t<level_t>>(lhs) &
			static_cast<std::underlying_type_t<level_t>>(rhs)
			);
	}
}

namespace lwlog::level
{
	using level_underlying_type = std::underlying_type_t<level_t>;

	static level_underlying_type level_value(level_t level)
	{
		return static_cast<level_underlying_type>(level);
	}

	static const char* level_to_string(level_t level)
	{
		switch (level)
		{
		case level_t::info:		return "info";		break;
		case level_t::warning:	return "warning";	break;
		case level_t::error:	return "error";		break;
		case level_t::critical:	return "critical";	break;
		case level_t::debug:	return "debug";		break;
		}
	}
}