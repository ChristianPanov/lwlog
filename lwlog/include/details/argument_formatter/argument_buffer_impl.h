#pragma once

#include "argument_buffer.h"

namespace lwlog::details::log_args
{
    template<std::size_t Capacity>
    template<typename... Args>
    void argument_buffer<Capacity>::capture(Args&& ...args)
    {
        m_size = 0;
        m_count = 0;

        (this->encode(std::forward<Args>(args)), ...);
    }

    template<std::size_t Capacity>
    template<typename T>
    T argument_buffer<Capacity>::decode_scalar(std::size_t& cursor) const
    {
        T value;
        std::memcpy(&value, m_data + cursor, sizeof(T));
        cursor += sizeof(T);

        return value;
    }

    template<std::size_t Capacity>
    std::string_view argument_buffer<Capacity>::decode_string(std::size_t& cursor) const
    {
        std::uint16_t length;
        std::memcpy(&length, m_data + cursor, sizeof(length));
        cursor += sizeof(length);

        const char* str{ reinterpret_cast<const char*>(m_data + cursor) };
        cursor += length;

        return std::string_view{ str, length };
    }

    template<std::size_t Capacity>
    argument_type argument_buffer<Capacity>::decode_type(std::size_t& cursor) const
    {
        return static_cast<argument_type>(m_data[cursor++]);
    }

    template<std::size_t Capacity>
    std::uint8_t argument_buffer<Capacity>::count() const
    { 
        return m_count; 
    }

    template<std::size_t Capacity>
    template<typename T>
    void argument_buffer<Capacity>::encode(T&& value)
    {
        using Type = std::decay_t<T>;

        if constexpr (std::is_same_v<Type, bool>)
        {
            this->encode_scalar(argument_type::boolean, value);
        }
        else if constexpr (std::is_same_v<Type, char>)
        {
            this->encode_scalar(argument_type::character, value);
        }
        else if constexpr (std::is_integral_v<Type> && std::is_signed_v<Type>)
        {
            this->encode_scalar(argument_type::int64, static_cast<std::int64_t>(value));
        }
        else if constexpr (std::is_integral_v<Type> && std::is_unsigned_v<Type>)
        {
            this->encode_scalar(argument_type::uint64, static_cast<std::uint64_t>(value));
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            this->encode_scalar(argument_type::f32, static_cast<float>(value));
        }
        else if constexpr (std::is_floating_point_v<Type>)
        {
            this->encode_scalar(argument_type::f64, static_cast<double>(value));
        }
        else if constexpr (std::is_same_v<Type, std::string_view> || std::is_same_v<Type, std::string>)
        {
            this->encode_string(value.data(), value.size());
        }
        else if constexpr (std::is_same_v<Type, const char*> || std::is_same_v<Type, char*>)
        {
            this->encode_string(value ? value : "", value ? std::strlen(value) : 0);
        }
    }

    template<std::size_t Capacity>
    template<typename T>
    void argument_buffer<Capacity>::encode_scalar(argument_type type, T value)
    {
        m_data[m_size++] = static_cast<std::uint8_t>(type);
        std::memcpy(m_data + m_size, &value, sizeof(T));
        m_size += sizeof(T);
        ++m_count;
    }

    template<std::size_t Capacity>
    void argument_buffer<Capacity>::encode_string(const char* str, std::size_t size)
    {
        const std::size_t header_end{ m_size + 1U + sizeof(std::uint16_t) };
        const std::size_t avail{ Capacity > header_end ? Capacity - header_end : 0 };
        const std::uint16_t len{ static_cast<std::uint16_t>(size < avail ? size : avail) };

        m_data[m_size++] = static_cast<std::uint8_t>(argument_type::string);
        std::memcpy(m_data + m_size, &len, sizeof(len));
        m_size += sizeof(len);
        std::memcpy(m_data + m_size, str, len);
        m_size += len;
        ++m_count;
    }
}