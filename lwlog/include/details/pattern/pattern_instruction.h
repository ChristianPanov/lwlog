#pragma once

#include <cstddef>
#include <string_view>
#include <vector>

namespace lwlog::details::pattern_bytecode
{
    static constexpr std::uint16_t invalid_custom_index{ 0xFFFFU };

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

        sgr_begin,
        sgr_reset, 
        sgr_begin_level
    };
     
    enum class field_id : std::uint8_t
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
        char seq[6]; 
        std::uint8_t size; 
    };

    struct field_noalign_payload 
    { 
        field_id id; 
    };

    struct field_align_payload 
    { 
        field_id id; 
        char fill_char; 
        std::uint8_t width; 
    };

    struct custom_field_noalign_payload
    {
        std::uint16_t index;
        std::uint16_t token_offset;
        std::uint16_t token_size;
        std::uint16_t name_offset;
        std::uint8_t  name_size;
    };

    struct custom_field_align_payload
    {
        std::uint16_t index;
        std::uint16_t token_offset;
        std::uint16_t token_size;
        std::uint16_t name_offset;
        std::uint8_t  name_size;
        char fill_char;
        std::uint8_t  width;
    };

    struct instruction
    {
        op_code code{ op_code::literal };

        union 
        {
            literal_payload literal;

            field_align_payload field_align;
            field_noalign_payload field_noalign;

            custom_field_noalign_payload custom_field_noalign;
            custom_field_align_payload custom_field_align;

            sgr_payload sgr;
        } u;

        static instruction make_literal(std::uint16_t offset, std::uint16_t size);

        static instruction make_field_noalign(field_id id);
        static instruction make_field_left(field_id id, const alignment_info& alignment);
        static instruction make_field_right(field_id id, const alignment_info& alignment);
        static instruction make_field_center(field_id id, const alignment_info& alignment);

        static instruction make_custom_field_noalign(std::uint16_t token_offset, std::uint16_t token_size,
            std::uint16_t name_offset, std::uint8_t name_size);
        static instruction make_custom_field_left(std::uint16_t token_offset, std::uint16_t token_size,
            std::uint16_t name_offset, std::uint8_t name_size, const alignment_info& alignment);
        static instruction make_custom_field_right(std::uint16_t token_offset, std::uint16_t token_size,
            std::uint16_t name_offset, std::uint8_t name_size, const alignment_info& alignment);
        static instruction make_custom_field_center(std::uint16_t token_offset, std::uint16_t token_size,
            std::uint16_t name_offset, std::uint8_t name_size, const alignment_info& alignment);

        static instruction make_sgr_begin(std::uint8_t code);
        static instruction make_sgr_end();
        static instruction make_sgr_begin_level();
    };

    using instruction_list = std::vector<instruction>;
}