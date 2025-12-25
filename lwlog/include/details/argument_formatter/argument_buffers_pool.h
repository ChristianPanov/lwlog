#pragma once

namespace lwlog::details
{
    template<typename BufferLimits>
    struct args_slot
    {
        char args[BufferLimits::arg_count][BufferLimits::argument];
        std::uint16_t lengths[BufferLimits::arg_count];
    };

    template<typename BufferLimits>
    class argument_buffers_pool
    {
        static constexpr std::uint8_t invalid{ 0xFF };

    public:
        argument_buffers_pool();

        std::uint8_t acquire_args_buffer();
        void release_args_buffer(std::uint8_t slot_index);

        args_slot<BufferLimits>& get_slot(std::uint8_t slot_index);
        const args_slot<BufferLimits>& get_slot(std::uint8_t slot_index) const;

    private:
        args_slot<BufferLimits> m_slots[BufferLimits::pool_size];
        std::uint8_t m_next[BufferLimits::pool_size];
        std::atomic<std::uint8_t> m_head;
    };
}

#include "argument_buffers_pool_impl.h"