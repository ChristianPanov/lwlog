#pragma once

namespace lwlog::details
{
	struct duplex
	{
		std::string first;
		std::string second;

		bool operator==(const duplex& dup) const noexcept
		{
			return ((first == dup.first) || (second == dup.second) || 
				(first == dup.second) || (second == dup.first));
		}
	};
}

namespace std
{
	template <>
	struct std::hash<lwlog::details::duplex>
	{
		std::size_t operator()(const lwlog::details::duplex& dup) const noexcept
		{
			return std::hash<std::string>{}(dup.first) ^ std::hash<std::string>{}(dup.second);
		}
	};
}
