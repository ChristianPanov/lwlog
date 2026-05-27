#include "bounded_queue_storage.h"
#pragma once

namespace lwlog::details
{
    template<typename T, std::size_t Capacity>
    template<typename... Args>
    void bounded_queue_storage<T, Capacity>::construct_at(std::size_t index, Args&&... args)
    {
        ::new(static_cast<void*>(this->ptr_at(index))) T{ std::forward<Args>(args)... };
    }

    template<typename T, std::size_t Capacity>
    T* bounded_queue_storage<T, Capacity>::ptr_at(std::size_t index)
    {
        const std::size_t wrapped_index{ index & index_mask };
        const std::size_t slot_byte_offset{ wrapped_index * sizeof(T) };

        std::byte* const slot_address_as_bytes{ m_storage + slot_byte_offset };
        T* const slot_address_as_type{ reinterpret_cast<T*>(slot_address_as_bytes) };

        return std::launder(slot_address_as_type);
    }

    template<typename T, std::size_t Capacity>
    const T* bounded_queue_storage<T, Capacity>::ptr_at(std::size_t index) const
    {
        const std::size_t wrapped_index{ index & index_mask };
        const std::size_t slot_byte_offset{ wrapped_index * sizeof(T) };

        const std::byte* const slot_address_as_bytes{ m_storage + slot_byte_offset };
        const T* const slot_address_as_type{ reinterpret_cast<const T*>(slot_address_as_bytes) };

        return std::launder(slot_address_as_type);
    }

    template<typename T, std::size_t Capacity>
    void bounded_queue_storage<T, Capacity>::destroy_at(std::size_t index)
    {
        this->ptr_at(index)->~T();
    }
}