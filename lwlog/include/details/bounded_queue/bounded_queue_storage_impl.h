#pragma once

namespace lwlog::details
{
    template<typename T, std::size_t Capacity>
    template<typename... Args>
    void bounded_queue_storage<T, Capacity>::construct_at(std::size_t index, Args&&... args)
    {
        ::new(static_cast<void*>(this->slot_ptr(index))) T{ std::forward<Args>(args)... };
    }

    template<typename T, std::size_t Capacity>
    T bounded_queue_storage<T, Capacity>::extract_at(std::size_t index)
    {
        T* const slot{ this->slot_ptr(index) };
        T out{ std::move(*slot) };

        slot->~T();

        return out;
    }

    template<typename T, std::size_t Capacity>
    T* bounded_queue_storage<T, Capacity>::slot_ptr(std::size_t index)
    {
        const std::size_t wrapped_index{ index & index_mask };
        const std::size_t slot_byte_offset{ wrapped_index * sizeof(T) };

        std::byte* const slot_address_as_bytes{ m_storage + slot_byte_offset };
        T* const slot_address_as_type{ reinterpret_cast<T*>(slot_address_as_bytes) };

        return std::launder(slot_address_as_type);
    }
}