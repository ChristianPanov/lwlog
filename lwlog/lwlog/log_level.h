#pragma once

#include <type_traits>

namespace lwlog
{
	enum class level
	{
		none =		(1 << 0),
		info =		(1 << 1),
		warning =	(1 << 2),
		error =		(1 << 3),
		critical =	(1 << 4),
		debug =		(1 << 5),
		all =		(1 << 6)
	};

	static level operator|(level lhs, level rhs)
	{
		return static_cast<level> (
			static_cast<std::underlying_type<level>::type>(lhs)
			| static_cast<std::underlying_type<level>::type>(rhs)
			);
	}

	static level operator&(level lhs, level rhs)
	{
		return static_cast<level> (
			static_cast<std::underlying_type<level>::type>(lhs)
			& static_cast<std::underlying_type<level>::type>(rhs)
			);
	}
}