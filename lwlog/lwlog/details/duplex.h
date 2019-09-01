#pragma once

#include <functional>

namespace details
{
	template <typename First = std::string_view, typename Second = std::string_view>
	struct duplex
	{
		First first;
		Second second;

		bool operator==(const duplex& other) const
		{
			return (first == other.first
				&& second == other.second);
		}
	};

	template <typename First, typename Second>
	struct std::hash<details::duplex<First, Second>>
	{
		std::size_t operator()(const details::duplex<First, Second>& dup) const
		{
			return ((std::hash<First>()(dup.first)
				^ (std::hash<Second>()(dup.second) << 1)) >> 1);
		}
	};
}
