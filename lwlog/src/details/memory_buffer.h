#pragma once

#include <cstring>
#include <cstddef>
#include <memory>
#include <string_view>
#include <charconv>

namespace lwlog::details
{
    template<std::size_t Capacity>
    class memory_buffer
    {
    public:
        memory_buffer();

    private:
        void grow(std::size_t new_capacity);

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
        char m_inline_buffer[Capacity]{};
        char* m_buffer{ nullptr };

        std::size_t m_size{};
        std::size_t m_capacity{};
    };

    template<typename T>
    void convert_to_chars(char* const __restrict buffer, std::size_t buffer_size, const T& value);
}

#include "memory_buffer_impl.h"