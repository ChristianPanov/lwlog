#pragma once

#include <cstdint>
#include <array>

namespace lwlog::details::pattern_bytecode
{
    static constexpr std::uint8_t invalid_custom_index{ 255 };

    enum class op_code : std::uint8_t
    {
        literal,

        field_noalign,
        field_align_left,
        field_align_right,
        field_align_center,

        custom_field_noalign,
        custom_field_align_left,
        custom_field_align_right,
        custom_field_align_center,

        sgr,
        sgr_level
    };
     
    enum class builtin_field : std::uint8_t
    {
        level,
        message,
        thread_id,
        process_id,

        line,
        file,
        path,
        function,

        topic,
        full_topic,

        date,
        date_short,
        year,
        year_short,

        month,
        month_name,
        month_name_short,

        day,
        weekday,
        weekday_short,

        time,
        hour_clock_24,
        hour_clock_12,
        ampm,

        hour_24,
        hour_12,
        minute,
        second,
        millisecond,
        microsecond,
        nanosecond
    };

    struct alignment_info
    {
        char fill_char;
        char side_char;
        std::uint8_t width;
    };

    struct literal_payload 
    { 
        std::uint16_t offset; 
        std::uint16_t size;
    };

    struct sgr_payload 
    { 
        std::uint8_t code; 
    };

    struct field_noalign_payload 
    { 
        builtin_field field;
    };

    struct field_align_payload 
    { 
        builtin_field field;
        char fill_char; 
        std::uint8_t width; 
    };

    struct custom_field_noalign_payload
    {
        std::uint16_t field_offset;
        std::uint16_t name_offset;
        std::uint8_t field_size;
        std::uint8_t name_size;
        std::uint8_t index;
    };

    struct custom_field_align_payload
    {
        std::uint16_t field_offset;
        std::uint16_t name_offset;
        std::uint8_t field_size;
        std::uint8_t name_size;
        std::uint8_t index;
        char fill_char;
        std::uint8_t width;
    };

    struct instruction
    {
        op_code code;

        union 
        {
            literal_payload literal;

            field_noalign_payload field_noalign;
            field_align_payload field_align;

            custom_field_noalign_payload custom_field_noalign;
            custom_field_align_payload custom_field_align;

            sgr_payload sgr;
        } u;

        static instruction make_literal(std::uint16_t offset, std::uint16_t size);

        static instruction make_field_noalign(builtin_field field);
        static instruction make_field_aligned(builtin_field field, const alignment_info& alignment);

        static instruction make_custom_field_noalign(std::uint16_t field_offset, std::uint16_t name_offset, 
            std::uint8_t field_size, std::uint8_t name_size);
        static instruction make_custom_field_aligned(std::uint16_t field_offset, std::uint16_t name_offset, 
            std::uint8_t field_size, std::uint8_t name_size, const alignment_info& alignment);

        static instruction make_sgr(std::uint8_t code);
        static instruction make_sgr_level();
    };

    class instruction_list
    {
        static constexpr std::uint8_t capacity{ 32 };

    public:
        void push_back(const instruction& instr) { m_data[m_size++] = instr; }
        void clear()                             { m_size = 0;               }
        void resize(std::uint8_t n)              { m_size = n;               }
        std::uint8_t size() const                { return m_size;            }

    public:
        instruction* begin()             { return m_data.data();            }
        instruction* end()               { return m_data.data() + m_size;   }
        const instruction* begin() const { return m_data.data();            }
        const instruction* end()   const { return m_data.data() + m_size;   }

    private:
        std::array<instruction, capacity> m_data;
        std::uint8_t m_size{ 0 };
    };
}