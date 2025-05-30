#pragma once

#include <string>
#include <variant>
#include <functional>

#include "level.h"
#include "details/memory_buffer.h"

namespace lwlog::details
{
	struct flag_pair
	{
		std::string_view verbose;
		std::string_view shortened;
	};

	template<typename... Ts>
	using ref_variant = std::variant<std::reference_wrapper<Ts>...>;

	using attrib_value = ref_variant<int, float, double, std::string_view, level>;
	using attrib_callback_t = std::function<void(char*, std::size_t)>;

	struct attribute
	{
		attribute(std::string_view flag, attrib_value value, const attrib_callback_t& callback);
		attribute(std::string_view flag, attrib_value value);

		std::string_view flag;
		attrib_value value;
		attrib_callback_t value_conv_callback;
	};
}