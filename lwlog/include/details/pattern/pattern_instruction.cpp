#include "pattern_instruction.h"

namespace lwlog::details::pattern_bytecode
{
    instruction instruction::make_literal(std::uint16_t offset, std::uint16_t size)
    {
        instruction instr{};
        instr.code = op_code::literal;
        instr.u.literal = literal_payload{ offset, size };

        return instr;
    }

    instruction instruction::make_field_noalign(field_id id)
    {
        instruction instr{};
        instr.code = op_code::field_noalign;
        instr.u.field_noalign = field_noalign_payload{ id };

        return instr;
    }

    instruction instruction::make_field_left(field_id id, const alignment_info& alignment)
    {
        instruction instr{};
        instr.code = op_code::field_align_left;
        instr.u.field_align = field_align_payload{ id, alignment.fill_char, alignment.width };

        return instr;
    }

    instruction instruction::make_field_right(field_id id, const alignment_info& alignment)
    {
        instruction instr{};
        instr.code = op_code::field_align_right;
        instr.u.field_align = field_align_payload{ id, alignment.fill_char, alignment.width };

        return instr;
    }

    instruction instruction::make_field_center(field_id id, const alignment_info& alignment)
    {
        instruction instr{};
        instr.code = op_code::field_align_center;
        instr.u.field_align = field_align_payload{ id, alignment.fill_char, alignment.width };

        return instr;
    }

    instruction instruction::make_custom_field_noalign(std::uint16_t token_offset, std::uint16_t token_size,
        std::uint16_t name_offset, std::uint8_t name_size)
    {
        instruction instr{};
        instr.code = op_code::custom_field_noalign;
        instr.u.custom_field_noalign = { invalid_custom_index, token_offset, token_size, name_offset, name_size };

        return instr;
    }

    instruction instruction::make_custom_field_left(std::uint16_t token_offset, std::uint16_t token_size,
        std::uint16_t name_offset, std::uint8_t name_size, const alignment_info& alignment)
    {
        instruction instr{};
        instr.code = op_code::custom_field_align_left;
        instr.u.custom_field_align = { invalid_custom_index, token_offset, token_size,
            name_offset, name_size, alignment.fill_char, alignment.width };

        return instr;
    }

    instruction instruction::make_custom_field_right(std::uint16_t token_offset, std::uint16_t token_size,
        std::uint16_t name_offset, std::uint8_t name_size, const alignment_info& alignment)
    {
        instruction instr{};
        instr.code = op_code::custom_field_align_right;
        instr.u.custom_field_align = { invalid_custom_index, token_offset, token_size,
            name_offset, name_size, alignment.fill_char, alignment.width };

        return instr;
    }

    instruction instruction::make_custom_field_center(std::uint16_t token_offset, std::uint16_t token_size,
        std::uint16_t name_offset, std::uint8_t name_size, const alignment_info& alignment)
    {
        instruction instr{};
        instr.code = op_code::custom_field_align_center;
        instr.u.custom_field_align = { invalid_custom_index, token_offset, token_size,
            name_offset, name_size, alignment.fill_char, alignment.width };

        return instr;
    }

    instruction instruction::make_sgr_begin(std::uint8_t code)
    {
        instruction instr{};
        instr.code = op_code::sgr_begin;

        char* seq{ instr.u.sgr.seq };
        std::uint8_t n{ 2 };

        seq[0] = '\x1b';
        seq[1] = '[';

        if (code >= 100)
        {
            seq[n++] = '1';
            seq[n++] = char('0' + (code / 10) % 10);
            seq[n++] = char('0' + (code % 10));
        }
        else
        {
            seq[n++] = char('0' + (code / 10));
            seq[n++] = char('0' + (code % 10));
        }

        seq[n++] = 'm';
        instr.u.sgr.size = n;

        return instr;
    }

    instruction instruction::make_sgr_end()
    {
        instruction instr{};
        instr.code = op_code::sgr_reset;

        return instr;
    }

    instruction instruction::make_sgr_begin_level()
    {
        instruction instr{};
        instr.code = op_code::sgr_begin_level;

        return instr;
    }
}