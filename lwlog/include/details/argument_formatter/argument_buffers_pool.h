#pragma once

#include "argument.h"

namespace lwlog::details::async_args
{
    template<typename BufferLimits>
    struct args_slot
    {
        template<typename T>
        void set(std::uint8_t index, T&& value);

        argument args[BufferLimits::arg_count];
        char string_storage[BufferLimits::arg_count][BufferLimits::argument];
    };

    template<typename BufferLimits>
    class pool
    {
        static constexpr std::uint8_t invalid{ 0xFF };

    public:
        pool();

        std::uint8_t acquire_slot_index();
        void release_slot_index(std::uint8_t slot_index);

        args_slot<BufferLimits>& get_slot(std::uint8_t slot_index);
        const args_slot<BufferLimits>& get_slot(std::uint8_t slot_index) const;

    private:
        args_slot<BufferLimits> m_slots[BufferLimits::pool_size];
        std::uint8_t m_next[BufferLimits::pool_size];
        std::atomic<std::uint8_t> m_head;
    };
}

#include "argument_buffers_pool_impl.h"