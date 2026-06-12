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

    instruction instruction::make_field_noalign(builtin_field field)
    {
        instruction instr{};
        instr.code = op_code::field_noalign;
        instr.u.field_noalign = field_noalign_payload{ field };

        return instr;
    }

    instruction instruction::make_field_aligned(builtin_field field, const alignment_info& alignment)
    {
        instruction instr{};
        instr.u.field_align = field_align_payload{ field, alignment.fill_char, alignment.width };

        switch (alignment.side_char)
        {
        case '<': instr.code = op_code::field_align_left; break;
        case '>': instr.code = op_code::field_align_right; break;
        case '^': instr.code = op_code::field_align_center; break;
        }

        return instr;
    }

    instruction instruction::make_custom_field_noalign(std::uint16_t field_offset, std::uint16_t name_offset, 
        std::uint8_t field_size, std::uint8_t name_size)
    {
        instruction instr{};
        instr.code = op_code::custom_field_noalign;
        instr.u.custom_field_noalign = custom_field_noalign_payload{ field_offset, name_offset, 
            field_size, name_size, invalid_custom_index };

        return instr;
    }

    instruction instruction::make_custom_field_aligned(std::uint16_t field_offset, std::uint16_t name_offset,
        std::uint8_t field_size, std::uint8_t name_size, const alignment_info& alignment)
    {
        instruction instr{};
        instr.u.custom_field_align = custom_field_align_payload{ field_offset, name_offset, field_size, name_size, 
            invalid_custom_index, alignment.fill_char, alignment.width };

        switch (alignment.side_char)
        {
        case '<': instr.code = op_code::custom_field_align_left; break;
        case '>': instr.code = op_code::custom_field_align_right; break;
        case '^': instr.code = op_code::custom_field_align_center; break;
        }

        return instr;
    }

    instruction instruction::make_sgr(std::uint8_t code)
    { 
        instruction instr{};
        instr.code = op_code::sgr;
        instr.u.sgr = sgr_payload{ code };

        return instr;
    }

    instruction instruction::make_sgr_level()
    {
        instruction instr{};
        instr.code = op_code::sgr_level;

        return instr;
    }
}