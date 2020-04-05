#pragma once

namespace lwlog::details
{
	template <typename Ty1, typename Ty2>
	struct duplex
	{
		Ty1 first;
		Ty2 second;

		bool operator==(const duplex<Ty1, Ty2>& dup) const
		{
			return (first == dup.first
				&& second == dup.second);
		}
	};

	template <typename Ty1, typename Ty2>
	struct std::hash<lwlog::details::duplex<Ty1, Ty2>>
	{
		std::size_t operator()(const lwlog::details::duplex<Ty1, Ty2>& dup) const
		{
			return std::hash<Ty1>{}(dup.first) ^ std::hash<Ty2>{}(dup.second);
		}
	};
}
