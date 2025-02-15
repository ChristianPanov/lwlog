#pragma once

namespace lwlog::details
{
    template<typename BufferLimits>
    class argument_buffers_pool
    {
    public:        
        argument_buffers_pool();
        std::uint8_t acquire_args_buffer();
        void release_args_buffer(std::uint8_t idx);
        char(*get_args_buffer(std::uint8_t idx))[BufferLimits::arg_count][BufferLimits::argument];

    private:
        char m_args_buffers[BufferLimits::pool_size][BufferLimits::arg_count][BufferLimits::argument];
        std::uint8_t m_args_buffers_free_indices[BufferLimits::pool_size];
        std::atomic<std::uint8_t> m_args_buffers_free_top;
    };
}

#include "argument_buffers_pool_impl.h"