#pragma once

namespace lwlog::details
{
    template<std::size_t Capacity>
    void memory_buffer<Capacity>::append(const char* data, std::size_t size)
    {
        if (m_size + size <= Capacity)
        {
            std::memcpy(m_buffer + m_size, data, size);
            m_size += size;
        }
    }

    template<std::size_t Capacity>
    void lwlog::details::memory_buffer<Capacity>::append(std::string_view data)
    {
        memory_buffer::append(data.data(), data.size());
    }

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::append(char ch)
    {
        if (m_size + 1 <= Capacity)
        {
            m_buffer[m_size++] = ch;
        }
    }

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::replace(std::size_t to_replace_pos, std::size_t to_replace_size,
        const char* const __restrict replace_with, std::size_t replace_with_size)
    {
        if(m_size - to_replace_size + replace_with_size <= Capacity)
        {
            char* const __restrict shift_dest{ m_buffer + to_replace_pos + replace_with_size };
            const char* const __restrict shift_source{ m_buffer + to_replace_pos + to_replace_size };
            const std::size_t shift_size{ m_size - (to_replace_pos + to_replace_size) };

            std::memcpy(shift_dest, shift_source, shift_size);
            std::memcpy(m_buffer + to_replace_pos, replace_with, replace_with_size);

            m_size = m_size - to_replace_size + replace_with_size;
        }
    }

    template<std::size_t Capacity>
    void memory_buffer<Capacity>::insert(std::size_t insert_pos, std::size_t insert_size, 
        const char* const __restrict to_insert)
    {
        if (m_size + insert_size <= Capacity)
        {
            char* const __restrict shift_dest{ m_buffer + insert_pos + insert_size };
            const char* const __restrict shift_source{ m_buffer + insert_pos };
            const std::size_t shift_size{ m_size - insert_pos };

            std::memcpy(shift_dest, shift_source, shift_size);
            std::memcpy(m_buffer + insert_pos, to_insert, insert_size);

            m_size += insert_size;
        }
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
        if (m_size <= Capacity)
        {
            m_buffer[m_size] = '\0';
            return m_buffer;
        }
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
}