#pragma once

namespace lwlog::details
{
    template<std::size_t Capacity>
    memory_buffer<Capacity>::memory_buffer()
        : m_buffer{ m_inline_buffer }
        , m_capacity{ Capacity }
    {}

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::grow(std::size_t new_capacity)
    {
        char* const new_buffer{ new char[new_capacity] };

        if (m_size > 0)
        {
            std::memcpy(new_buffer, m_buffer, m_size);
        }

        if (m_buffer != m_inline_buffer)
        {
            delete[] m_buffer;
            m_buffer = nullptr;
        }

        m_buffer = new_buffer;
        m_capacity = new_capacity;
    }

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::append(const char* data, std::size_t size)
    {
        if (m_size + size > m_capacity)
        {
            memory_buffer<Capacity>::grow(m_capacity * 1.5f);
        }

        std::memcpy(m_buffer + m_size, data, size);
        m_size += size;
    }

    template<std::size_t Capacity>
    void lwlog::details::memory_buffer<Capacity>::append(std::string_view data)
    {
        memory_buffer::append(data.data(), data.size());
    }

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::append(char ch)
    {
        if (m_size + 1 > m_capacity)
        {
            memory_buffer<Capacity>::grow(m_capacity * 1.5f);
        }

        m_buffer[m_size++] = ch;
    }

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::replace(std::size_t to_replace_pos, std::size_t to_replace_size,
        const char* const __restrict replace_with, std::size_t replace_with_size)
    {
        if(m_size - to_replace_size + replace_with_size > m_capacity)
        {
            memory_buffer<Capacity>::grow(m_capacity * 1.5f);
        }

        char* const __restrict shift_dest{ m_buffer + to_replace_pos + replace_with_size };
        const char* const __restrict shift_source{ m_buffer + to_replace_pos + to_replace_size };
        const std::size_t shift_size{ m_size - (to_replace_pos + to_replace_size) };

        std::memcpy(shift_dest, shift_source, shift_size);
        std::memcpy(m_buffer + to_replace_pos, replace_with, replace_with_size);

        m_size = m_size - to_replace_size + replace_with_size;
    }

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::insert(std::size_t insert_pos, std::size_t insert_size, 
        const char* const __restrict to_insert)
    {
        if (m_size + insert_size > m_capacity)
        {
            memory_buffer<Capacity>::grow(m_capacity * 1.5f);
        }

        char* const __restrict shift_dest{ m_buffer + insert_pos + insert_size };
        const char* const __restrict shift_source{ m_buffer + insert_pos };
        const std::size_t shift_size{ m_size - insert_pos };

        std::memcpy(shift_dest, shift_source, shift_size);
        std::memcpy(m_buffer + insert_pos, to_insert, insert_size);

        m_size += insert_size;
    }

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::erase(std::size_t erase_pos, std::size_t erase_size)
    {
        if (m_size - erase_size >= 0)
        {
            char* const __restrict shift_dest{ m_buffer + erase_pos };
            const char* const __restrict shift_source{ m_buffer + erase_pos + erase_size };
            const std::size_t shift_size{ m_size - erase_pos + erase_size };

            std::memcpy(shift_dest, shift_source, shift_size);
            m_size -= erase_size;
        }
    }

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::reset()
    {
        m_size = 0;
    }

    template<std::size_t Capacity>
    std::size_t memory_buffer<Capacity>::size() const
    {
        return m_size;
    }

    template<std::size_t Capacity>
    std::string_view memory_buffer<Capacity>::data() const
    {
        return std::string_view{ m_buffer, m_size };
    }

    template<std::size_t Capacity>
    const char* memory_buffer<Capacity>::c_str()
    {
        if (m_size < m_capacity)
        {
            m_buffer[m_size] = '\0';
        }

        return m_buffer;
    }

    template<std::size_t Capacity>
    char& memory_buffer<Capacity>::operator[](std::size_t index)
    {
        return m_buffer[index];
    }

    template<std::size_t Capacity>
    const char& memory_buffer<Capacity>::operator[](std::size_t index) const
    {
        return m_buffer[index];
    }

    template<typename T>
    void convert_to_chars(char* const __restrict buffer, std::size_t buffer_size, const T& value)
    {
        if constexpr (std::is_arithmetic_v<T>)
        {
            const auto [ptr, ec]{ std::to_chars(buffer, buffer + buffer_size, value) };
            buffer[ptr - buffer] = '\0';
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
                buffer[value_size] = '\0';
            }
            else if constexpr (std::is_same_v<T, const char*> || 
                std::is_same_v<T, char*>)
            {
                value_size = std::strlen(value);
                std::memcpy(buffer, value, value_size);
                buffer[value_size] = '\0';
            }
        }
    }
}