#pragma once

#include <cstddef>
#include <memory>
#include <string_view>
#include <charconv>

namespace lwlog::details
{
    template<std::size_t Capacity = 256>
    class memory_buffer
    {
    public:
        void append(const char* data, std::size_t size);
        void append(std::string_view data);
        void append(char ch);

        void replace(std::size_t to_replace_pos, std::size_t to_replace_size, 
            const char* const __restrict  replace_with, std::size_t replace_with_size);
        void insert(std::size_t insert_pos, std::size_t insert_size, const char* const __restrict to_insert);
        void erase(std::size_t erase_pos, std::size_t erase_size);
        void reset();

    public:
        std::size_t size() const;
        std::string_view data() const;
        const char* c_str();

    public:
        char& operator[](std::size_t index);
        const char& operator[](std::size_t index) const;

    private:
        char m_buffer[Capacity]{};
        std::size_t m_size{};
    };

    template<std::size_t Capacity = 256>
    std::size_t memory_buffer_find(const memory_buffer<Capacity>& buffer, const char* str, std::size_t offset = 0);

    template<std::size_t Capacity = 256>
    std::size_t memory_buffer_find(const memory_buffer<Capacity>& buffer, char ch, std::size_t offset = 0);

    template<typename T>
    std::size_t convert_to_chars(char* const __restrict buffer, std::size_t buffer_size, T value)
    {
		if constexpr (std::is_arithmetic_v<T>)
		{
			const std::to_chars_result res{ std::to_chars(buffer, buffer + buffer_size, value) };
			const std::uint8_t value_size = res.ptr - buffer;

            return value_size;
		}
		else if constexpr (std::is_same_v<T, std::string_view> ||
			std::is_same_v<T, std::string> ||
			std::is_same_v<T, const char*> || std::is_same_v<T, char*>)
		{
			std::size_t value_size{};

			if constexpr (std::is_same_v<T, std::string_view> ||
				std::is_same_v<T, std::string>)
			{
				value_size = value.size();
                std::memcpy(buffer, value.data(), value_size);
			}
			else if constexpr (std::is_same_v<T, const char*>)
			{
				value_size = std::strlen(value);
                std::memcpy(buffer, value, value_size);
			}
            else if constexpr (std::is_same_v<T, char*>)
            {
                value_size = std::strlen(value);
                std::memcpy(buffer, value, value_size);
            }

            return value_size;
		}

        return {};
    }
}

#include "memory_buffer_impl.h"