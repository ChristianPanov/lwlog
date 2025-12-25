#pragma once

namespace lwlog::details
{
    template<typename BufferLimits>
    argument_buffers_pool<BufferLimits>::argument_buffers_pool()
    {
        for (std::uint8_t i = 0; i < BufferLimits::pool_size - 1; ++i)
        {
            m_next[i] = static_cast<std::uint8_t>(i + 1);
        }

        m_next[BufferLimits::pool_size - 1] = invalid; 
        
        m_head.store(0, std::memory_order_release);
    }
    
    template<typename BufferLimits>
    std::uint8_t argument_buffers_pool<BufferLimits>::acquire_args_buffer()
    {
        for (;;)
        {
            std::uint8_t head{ m_head.load(std::memory_order_acquire) };
            if (head == invalid)
            {
                LWLOG_CPU_PAUSE();
                continue;
            }

            const std::uint8_t next{ m_next[head] };

            if (m_head.compare_exchange_weak(head, next, std::memory_order_acq_rel,std::memory_order_acquire))
            {
                return head;
            }
        }
    }

    template<typename BufferLimits>
    void argument_buffers_pool<BufferLimits>::release_args_buffer(std::uint8_t slot_index)
    {
        for (;;)
        {
            std::uint8_t head{ m_head.load(std::memory_order_acquire) };

            m_next[slot_index] = head;

            if (m_head.compare_exchange_weak(head, slot_index, std::memory_order_acq_rel, std::memory_order_acquire))
            {
                return;
            }
        }
    }

    template<typename BufferLimits>
    args_slot<BufferLimits>& argument_buffers_pool<BufferLimits>::get_slot(std::uint8_t slot_index)
    {
        return m_slots[slot_index];
    }

    template<typename BufferLimits>
    const args_slot<BufferLimits>& argument_buffers_pool<BufferLimits>::get_slot(std::uint8_t slot_index) const
    {
        return m_slots[slot_index];
    }
}