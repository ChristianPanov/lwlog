#pragma once

namespace lwlog::details::async_args
{
    template<typename BufferLimits>
    template<typename T>
    void args_slot<BufferLimits>::set(std::uint8_t index, T&& value)
    {
        using Type = std::remove_reference_t<T>;
        auto& arg_ref = args[index];

        if constexpr (std::is_same_v<Type, bool>)
        {
            arg_ref.type = argument_type::boolean;
            arg_ref.u.b = std::forward<T>(value);
        }
        else if constexpr (std::is_same_v<Type, char>)
        {
            arg_ref.type = argument_type::character;
            arg_ref.u.ch = std::forward<T>(value);
        }
        else if constexpr (std::is_integral_v<Type> && std::is_signed_v<Type>)
        {
            arg_ref.type = argument_type::int64;
            arg_ref.u.i64 = std::forward<T>(value);
        }
        else if constexpr (std::is_integral_v<Type> && std::is_unsigned_v<Type>)
        {
            arg_ref.type = argument_type::uint64;
            arg_ref.u.u64 = std::forward<T>(value);
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            arg_ref.type = argument_type::f32;
            arg_ref.u.f32 = std::forward<T>(value);
        }
        else if constexpr (std::is_floating_point_v<Type>)
        {
            arg_ref.type = argument_type::f64;
            arg_ref.u.f64 = std::forward<T>(value);
        }
        else if constexpr (std::is_same_v<Type, std::string_view> ||
            std::is_same_v<Type, std::string>)
        {
            std::size_t value_size{ value.size() };
            std::memcpy(string_storage[index], value.data(), value_size);

            arg_ref.type = argument_type::string;
            arg_ref.u.str = string_ref{ string_storage[index], static_cast<std::uint16_t>(value_size) };
        }
        else if constexpr (std::is_same_v<std::decay_t<Type>, const char*> ||
            std::is_same_v<std::decay_t<Type>, char*>)
        {
            const char* str{ value ? value : "" };

            std::size_t value_size{ std::strlen(str) };
            std::memcpy(string_storage[index], str, value_size);

            arg_ref.type = argument_type::string;
            arg_ref.u.str = string_ref{ string_storage[index], static_cast<std::uint16_t>(value_size) };
        }
    }

    template<typename BufferLimits>
    pool<BufferLimits>::pool()
    {
        for (std::uint8_t i = 0; i < BufferLimits::pool_size - 1; ++i)
        {
            m_next[i] = static_cast<std::uint8_t>(i + 1);
        }

        m_next[BufferLimits::pool_size - 1] = invalid; 
        
        m_head.store(0, std::memory_order_release);
    }
    
    template<typename BufferLimits>
    std::uint8_t pool<BufferLimits>::acquire_slot_index()
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
    void pool<BufferLimits>::release_slot_index(std::uint8_t slot_index)
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
    args_slot<BufferLimits>& pool<BufferLimits>::get_slot(std::uint8_t slot_index)
    {
        return m_slots[slot_index];
    }

    template<typename BufferLimits>
    const args_slot<BufferLimits>& pool<BufferLimits>::get_slot(std::uint8_t slot_index) const
    {
        return m_slots[slot_index];
    }
}