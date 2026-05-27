#pragma once

#include <utility>
#include <new>
#include <cstddef>

namespace lwlog::details
{
    template<typename T, std::size_t Capacity>
    class bounded_queue_storage
    {
        static constexpr auto index_mask{ Capacity - 1 };

    public:
        template<typename... Args>
        void construct_at(std::size_t index, Args&&... args);

        T* ptr_at(std::size_t index);
        const T* ptr_at(std::size_t index) const;

        void destroy_at(std::size_t index);

    private:
        alignas(T) std::byte m_storage[Capacity * sizeof(T)];
    };
}

#include "bounded_queue_storage_impl.h"