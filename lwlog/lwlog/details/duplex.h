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

		template<typename T>
		friend bool operator==(const T& t, const duplex& dup)
		{
			if constexpr (std::is_convertible_v<T, Ty1>)
			{
				if (t == dup.first)
				{
					correct_val = t;
					return true;
				}
			}

			if constexpr (std::is_convertible_v<T, Ty2>)
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
			if constexpr (std::is_convertible_v<T, Ty1>)
			{
				if (t == dup.first)
				{
					correct_val = t;
					return true;
				}
			}

			if constexpr (std::is_convertible_v<T, Ty2>)
			{
				if (t == dup.second)
				{
					correct_val = t;
					return true;
				}
			}

			return false;
		}
	};

	template <typename Ty1, typename Ty2>
	struct std::hash<lwlog::details::duplex<Ty1, Ty2>>
	{
		std::size_t operator()(const lwlog::details::duplex<Ty1, Ty2>& dup) const
		{
			return ((std::hash<Ty1>()(dup.first)
				^ (std::hash<Ty2>()(dup.second) << 1)) >> 1);
		}
	};
}
