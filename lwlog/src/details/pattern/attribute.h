#pragma once

#include <variant>

namespace lwlog::details
{
	struct flag_pair
	{
		std::string_view verbose;
		std::string_view shortened;
		bool operator==(const flag_pair& other) const
		{
			return (verbose == other.verbose) &&
				(shortened == other.shortened);
		}
	};

	using attrib_value = std::variant<
		std::reference_wrapper<int>,
		std::reference_wrapper<float>,
		std::reference_wrapper<double>,
		std::reference_wrapper<std::string_view>
	>;

	struct attrib_value_visitor
	{
		template<typename T>
		std::string_view operator()(T arg)
		{
			if constexpr (std::is_arithmetic_v<T::type>)
				return std::to_string(std::forward<T::type>(arg));
			else return arg;
		}
	};

	struct attribute
	{
		flag_pair flags;
		attrib_value value;
	};
}