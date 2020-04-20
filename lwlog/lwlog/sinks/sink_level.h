#pragma once

namespace lwlog
{
	enum class sink_level
	{
		none		=		(1 << 0),
		info		=		(1 << 1),
		warning		=		(1 << 2),
		error		=		(1 << 3),
		critical	=		(1 << 4),
		debug		=		(1 << 5),
		all			=		(1 << 6)
	};

	inline std::string level_to_string(sink_level level)
	{
		if (level == sink_level::info)			{ return "info"; }
		else if (level == sink_level::warning)	{ return "warning"; }
		else if (level == sink_level::error)	{ return "error"; }
		else if (level == sink_level::critical) { return "critical"; }
		else if (level == sink_level::debug)	{ return "debug"; }
	}
}