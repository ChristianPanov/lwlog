#pragma once

namespace lwlog::details
{
    template<typename BufferLimits>
    argument_buffers_pool<BufferLimits>::argument_buffers_pool()
        : m_args_buffers_free_top{ BufferLimits::pool_size }
    {
        for (std::uint8_t i = 0; i < BufferLimits::pool_size; ++i)
        {
            m_args_buffers_free_indices[i] = i;
        }
    }

    template<typename BufferLimits>
    std::uint8_t argument_buffers_pool<BufferLimits>::acquire_args_buffer()
    {
        for (;;) 
        {
            std::uint8_t top{ m_args_buffers_free_top.load(std::memory_order_acquire) };
            while (top > 0) 
            {
                if (m_args_buffers_free_top.compare_exchange_weak(top, static_cast<std::uint8_t>(top - 1),
                    std::memory_order_acq_rel, std::memory_order_acquire)) 
                {
                    return m_args_buffers_free_indices[top - 1];
                }
            }

            LWLOG_CPU_PAUSE();
        }
    }


    template<typename BufferLimits>
    void argument_buffers_pool<BufferLimits>::release_args_buffer(std::uint8_t slot_handle)
    {
        std::uint8_t old_top{ m_args_buffers_free_top.load(std::memory_order_acquire) };

        for (;;) 
        {
            if (old_top == BufferLimits::pool_size)
            {
                return;
            }

            const std::uint8_t new_top{ static_cast<std::uint8_t>(old_top + 1) };
            if (m_args_buffers_free_top.compare_exchange_weak(old_top, new_top, 
                std::memory_order_acq_rel, std::memory_order_acquire)) 
            {
                m_args_buffers_free_indices[old_top] = slot_handle;
                return;
            }
        }
    }

    template<typename BufferLimits>
    char(&argument_buffers_pool<BufferLimits>::get_args_buffer(std::uint8_t slot_index))
        [BufferLimits::arg_count][BufferLimits::argument]
    {
        return m_args_buffers[slot_index];
    }

    template<typename BufferLimits>
    const char(&argument_buffers_pool<BufferLimits>::get_args_buffer(std::uint8_t slot_index) const)
        [BufferLimits::arg_count][BufferLimits::argument]
    {
        return m_args_buffers[slot_index];
    }
}