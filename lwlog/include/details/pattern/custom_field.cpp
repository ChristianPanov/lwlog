#include "custom_field.h"

#include "details/memory_buffer.h"

namespace lwlog::details
{
    custom_field::custom_field(std::string_view name, custom_value value)
        : name{ name }
        , value{ value }
    {
        format_fn = [](const custom_value& value, char* buffer, std::size_t size) -> std::size_t
            {
                switch (value.index())
                {
                case 0: return convert_to_chars(buffer, size, std::get<0>(value).get());
                case 1: return convert_to_chars(buffer, size, std::get<1>(value).get());
                case 2: return convert_to_chars(buffer, size, std::get<2>(value).get());
                case 3: return convert_to_chars(buffer, size, std::get<3>(value).get());
                case 4: return convert_to_chars(buffer, size, std::get<4>(value).get());
                case 5: return convert_to_chars(buffer, size, std::get<5>(value).get());
                default: return 0;
                }
            };
    }

    custom_field::custom_field(std::string_view name, custom_value value, const custom_format_fn& fn)
        : name{ name }
        , value{ value }
        , format_fn{ fn }
    {}
}