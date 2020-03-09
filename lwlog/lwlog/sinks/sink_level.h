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
}