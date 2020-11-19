#pragma once

namespace lwlog
{
	enum class sink_level : std::uint8_t
	{
		none		=	(1 << 0),
		info		=	(1 << 1),
		warning		=	(1 << 2),
		error		=	(1 << 3),
		critical	=	(1 << 4),
		debug		=	(1 << 5),
		all			=	(1 << 6)
	};

	inline std::string level_to_string(sink_level level)
	{
		switch (level)
		{
		case sink_level::info:		return "info";		break;
		case sink_level::warning:	return "warning";	break;
		case sink_level::error:		return "error";		break;
		case sink_level::critical:	return "critical";	break;
		case sink_level::debug:		return "debug";		break;
		}
	}
}