#pragma once

#include <string>
#include <variant>
#include <functional>

namespace lwlog::details
{
	struct flag_pair
	{
		std::string_view verbose;
		std::string_view shortened;
	};

	template<typename... Ts>
	using ref_variant = std::variant<std::reference_wrapper<Ts>...>;
	using attrib_value = ref_variant<int, float, double, std::string, std::string_view, level>;

	struct attribute
	{
		attribute() = default;

		attribute(std::string_view flag, attrib_value value,
			std::function<const char*()> callback)
			: flag{ flag }
			, value{ value }
			, callback{ std::move(callback) }
		{}

		attribute(std::string_view flag, attrib_value value)
			: flag{ flag }
			, value{ value }
		{
			callback = [value]() -> const char* {
				switch (value.index())
				{
				case 0:	return std::to_string(std::get<0>(value).get()).c_str();
				case 1:	return std::to_string(std::get<1>(value).get()).c_str();
				case 2:	return std::to_string(std::get<2>(value).get()).c_str();
				case 3:	return std::get<3>(value).get().c_str();
				case 4:	return std::get<4>(value).get().data();
				}
			};
		}

		std::string_view flag;
		attrib_value value;
		std::function<const char*()> callback;
	};
}