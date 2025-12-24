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

        custom_noalign,
        custom_align_left,
        custom_align_right,
        custom_align_center,

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

    struct custom_noalign_payload
    {
        std::uint16_t index;
        std::uint16_t token_offset;
        std::uint16_t token_size;
        std::uint16_t name_offset;
        std::uint8_t  name_size;
    };

    struct custom_align_payload
    {
        std::uint16_t index;
        std::uint16_t token_offset;
        std::uint16_t token_size;
        std::uint16_t name_offset;
        std::uint8_t  name_size;
        char          fill_char;
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

            custom_noalign_payload custom_noalign;
            custom_align_payload custom_align;

            sgr_payload sgr;
        } u;

        static instruction make_literal(std::uint16_t offset, std::uint16_t size)
        {
            instruction instr{};
            instr.code = op_code::literal;
            instr.u.literal = literal_payload{ offset, size };

            return instr;
        }

        static instruction make_field_noalign(field_id id)
        {
            instruction instr{};
            instr.code = op_code::field_noalign;
            instr.u.field_noalign = field_noalign_payload{ id };

            return instr;
        }

        static instruction make_field_left(field_id id, const alignment_info& alignment)
        {
            instruction instr{};
            instr.code = op_code::field_align_left;
            instr.u.field_align = field_align_payload{ id, alignment.fill_char, alignment.width };

            return instr;
        }

        static instruction make_field_right(field_id id, const alignment_info& alignment)
        {
            instruction instr{};
            instr.code = op_code::field_align_right;
            instr.u.field_align = field_align_payload{ id, alignment.fill_char, alignment.width };

            return instr;
        }

        static instruction make_field_center(field_id id, const alignment_info& alignment)
        {
            instruction instr{};
            instr.code = op_code::field_align_center;
            instr.u.field_align = field_align_payload{ id, alignment.fill_char, alignment.width };

            return instr;
        }

        static instruction make_custom_noalign(std::uint16_t token_offset, std::uint16_t token_size, 
            std::uint16_t name_offset, std::uint8_t name_size)
        {
            instruction instr{};
            instr.code = op_code::custom_noalign;
            instr.u.custom_noalign = { invalid_custom_index, token_offset, token_size, name_offset, name_size };

            return instr;
        }

        static instruction make_custom_left(std::uint16_t token_offset, std::uint16_t token_size, 
            std::uint16_t name_offset, std::uint8_t name_size, const alignment_info& alignment)
        {
            instruction instr{};
            instr.code = op_code::custom_align_left;
            instr.u.custom_align = { invalid_custom_index, token_offset, token_size, 
                name_offset, name_size, alignment.fill_char, alignment.width };

            return instr;
        }

        static instruction make_custom_right(std::uint16_t token_offset, std::uint16_t token_size,
            std::uint16_t name_offset, std::uint8_t name_size, const alignment_info& alignment)
        {
            instruction instr{};
            instr.code = op_code::custom_align_right;
            instr.u.custom_align = { invalid_custom_index, token_offset, token_size,
                name_offset, name_size, alignment.fill_char, alignment.width };


            return instr;
        }

        static instruction make_custom_center(std::uint16_t token_offset, std::uint16_t token_size,
            std::uint16_t name_offset, std::uint8_t name_size, const alignment_info& alignment)
        {
            instruction instr{};
            instr.code = op_code::custom_align_center;
            instr.u.custom_align = { invalid_custom_index, token_offset, token_size,
                name_offset, name_size, alignment.fill_char, alignment.width };

            return instr;
        }

        static instruction make_sgr_begin(std::uint8_t code)
        {
            instruction i{};
            i.code = op_code::sgr_begin;

            char* s{ i.u.sgr.seq };
            s[0] = '\x1b'; 
            s[1] = '[';
            std::uint8_t n{ 2 };

            if (code >= 100) 
            { 
                s[n++] = '1'; 
                s[n++] = char('0' + (code / 10) % 10); 
                s[n++] = char('0' + (code % 10)); 
            }
            else 
            { 
                s[n++] = char('0' + (code / 10)); 
                s[n++] = char('0' + (code % 10)); 
            }

            s[n++] = 'm';
            i.u.sgr.size = n;

            return i;
        }

        static instruction make_sgr_end()
        {
            instruction instr{};
            instr.code = op_code::sgr_reset;

            return instr;
        }

        static instruction make_sgr_begin_level()
        {
            instruction i{};
            i.code = op_code::sgr_begin_level;

            return i;
        }
    };

    using instruction_list = std::vector<instruction>;
}