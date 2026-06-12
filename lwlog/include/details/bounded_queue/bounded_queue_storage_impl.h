#pragma once

#include "bounded_queue_storage.h"

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
        return std::launder(reinterpret_cast<T*>(m_storage + (index & index_mask) * sizeof(T)));
    }

    template<typename T, std::size_t Capacity>
    void bounded_queue_storage<T, Capacity>::destroy_at(std::size_t index)
    {
        this->ptr_at(index)->~T();
    }
}