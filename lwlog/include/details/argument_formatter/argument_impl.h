#pragma once

namespace lwlog::details::async_args
{
    template<typename BufferLimits>
    template<typename T>
    void captured_args<BufferLimits>::set(std::uint8_t index, T&& value)
    {
        using Type = std::decay_t<T>;
        auto& arg_ref = args[index];

        if constexpr (std::is_same_v<Type, bool>)
        {
            arg_ref.type = argument_type::boolean;
            arg_ref.u.b = std::forward<T>(value);
        }
        else if constexpr (std::is_same_v<Type, char>)
        {
            arg_ref.type = argument_type::character;
            arg_ref.u.ch = std::forward<T>(value);
        }
        else if constexpr (std::is_integral_v<Type> && std::is_signed_v<Type>)
        {
            arg_ref.type = argument_type::int64;
            arg_ref.u.i64 = std::forward<T>(value);
        }
        else if constexpr (std::is_integral_v<Type> && std::is_unsigned_v<Type>)
        {
            arg_ref.type = argument_type::uint64;
            arg_ref.u.u64 = std::forward<T>(value);
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            arg_ref.type = argument_type::f32;
            arg_ref.u.f32 = std::forward<T>(value);
        }
        else if constexpr (std::is_floating_point_v<Type>)
        {
            arg_ref.type = argument_type::f64;
            arg_ref.u.f64 = std::forward<T>(value);
        }
        else if constexpr (std::is_same_v<Type, std::string_view> ||
            std::is_same_v<Type, std::string>)
        {
            std::size_t value_size{ value.size() };
            std::memcpy(string_storage[index], value.data(), value_size);

            arg_ref.type = argument_type::string;
            arg_ref.u.str = string_ref{ string_storage[index], static_cast<std::uint16_t>(value_size) };
        }
        else if constexpr (std::is_same_v<Type, const char*> || std::is_same_v<Type, char*>)
        {
            const char* str{ value ? value : "" };

            std::size_t value_size{ std::strlen(str) };
            std::memcpy(string_storage[index], str, value_size);

            arg_ref.type = argument_type::string;
            arg_ref.u.str = string_ref{ string_storage[index], static_cast<std::uint16_t>(value_size) };
        }
    }
}