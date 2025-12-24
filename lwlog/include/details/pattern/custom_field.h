#pragma once

#include <string>
#include <variant>
#include <functional>

namespace lwlog::details
{
	struct flag_pair
	{
		std::string_view verbose;
		char shortened;
	};

    template<typename... Ts>
    using ref_variant = std::variant<std::reference_wrapper<Ts>...>;

    using custom_value = ref_variant<bool, int, float, double, std::string, std::string_view>;

    using custom_format_fn = std::size_t(*)(const custom_value& value, char* buffer, std::size_t size);

    struct custom_field
    {
        custom_field(std::string_view name, custom_value value);
        custom_field(std::string_view name, custom_value value, const custom_format_fn& fn);

        std::string_view name;
        custom_value value;
        custom_format_fn format_fn;
    };
}