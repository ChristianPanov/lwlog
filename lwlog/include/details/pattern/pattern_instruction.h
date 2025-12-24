#pragma once

#include <cstddef>
#include <string_view>
#include <vector>

namespace lwlog::details::pattern_bytecode
{
    enum class op_code : std::uint8_t
    {
        literal,
        field,
        sgr_begin,
        sgr_reset
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

    struct literal_payload  { std::uint16_t offset; std::uint16_t   size;   };
    struct field_payload    { field_id      id;     alignment_info  align;  };
    struct sgr_payload      { char          seq[6]; std::uint8_t    size;   };

    struct instruction
    {
        op_code code{ op_code::literal };

        union 
        {
            literal_payload literal;
            field_payload field;
            sgr_payload sgr;
        } u;

        static instruction make_literal(std::uint16_t offset, std::uint16_t size)
        {
            instruction instr{};
            instr.code = op_code::literal;
            instr.u.literal = literal_payload{ offset, size };

            return instr;
        }

        static instruction make_field(field_id id, const alignment_info& alignment)
        {
            instruction instr{};
            instr.code = op_code::field;
            instr.u.field = field_payload{ id, alignment };

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
    };

    using instruction_list = std::vector<instruction>;
}