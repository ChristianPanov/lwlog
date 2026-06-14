#pragma once

#include <cstdint>

namespace lwlog::details::log_args
{
    enum class argument_type : std::uint8_t
    {
        boolean,
        character,
        int64,
        uint64,
        f32,
        f64,
        string
    };

    template<std::size_t Capacity>
    class argument_buffer
    {
    public:
        template<typename... Args>
        void capture(Args&&... args);

        template<typename T> 
        T decode_scalar(std::size_t& cursor) const;
        std::string_view decode_string(std::size_t& cursor) const;
        argument_type decode_type(std::size_t& cursor) const;

        std::uint8_t count() const;

    private:
        template<typename T> 
        void encode(T&& value);
        template<typename T> 
        void encode_scalar(argument_type type, T value);
        void encode_string(const char* str, std::size_t size);

    private:
        std::uint8_t m_data[Capacity];
        std::uint16_t m_size{ 0 };
        std::uint8_t m_count{ 0 };
    };

    template<typename BufferLimits>
    using captured_args = argument_buffer<BufferLimits::arg_count * (BufferLimits::argument + 3)>;
}

#include "argument_buffer_impl.h"