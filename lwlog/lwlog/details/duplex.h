#pragma once

#include <functional>

namespace details
{
	template <typename First = std::string_view, typename Second = std::string_view>
	struct duplex
	{
		First first;
		Second second;

		bool operator==(const duplex<First, Second>& dup) const
		{
			return (first == dup.first
				&& second == dup.second);
		}

		template<typename T>
		friend bool operator==(const T& t, const duplex& dup)
		{
			if constexpr (std::is_convertible_v <T, First>)
			{
				if (t == dup.first)
				{
					correct_val = t;
					return true;
				}
			}

			if constexpr (std::is_convertible_v <T, Second>)
			{
				if (t == dup.second)
				{
					correct_val = t;
					return true;
				}
			}

			return false;
		}

		template<typename T>
		friend bool operator==(const duplex& dup, const T& t)
		{
			if constexpr (std::is_convertible_v <T, First>)
			{
				if (t == dup.first)
				{
					correct_val = t;
					return true;
				}
			}

			if constexpr (std::is_convertible_v <T, Second>) {
				if (t == dup.second)
				{
					correct_val = t;
					return true;
				}
			}

			return false;
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
