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
        std::uint8_t old_top{ m_args_buffers_free_top.load(std::memory_order_acquire) };
        while (old_top > 0)
        {
            if (m_args_buffers_free_top.compare_exchange_weak(old_top, old_top - 1, std::memory_order_acq_rel))
            {
                return m_args_buffers_free_indices[old_top - 1];
            }
        }

        return 0;
    }

    template<typename BufferLimits>
    void argument_buffers_pool<BufferLimits>::release_args_buffer(std::uint8_t idx)
    {
        std::uint8_t old_top{ m_args_buffers_free_top.load(std::memory_order_acquire) };
        while (old_top < static_cast<std::uint8_t>(BufferLimits::pool_size))
        {
            if (m_args_buffers_free_top.compare_exchange_weak(old_top, old_top + 1, std::memory_order_acq_rel))
            {
                m_args_buffers_free_indices[old_top] = idx;
                break;
            }
        }
    }
    template<typename BufferLimits>
    char(*argument_buffers_pool<BufferLimits>::get_args_buffer(std::uint8_t idx))[BufferLimits::arg_count][BufferLimits::argument]
    {
        return &m_args_buffers[idx];
    }
}