#pragma once

#include "context.h"
#include "ops.h"
#include "details/pattern/pattern_instruction.h"

namespace lwlog::details::pattern_executor
{
    template<typename BufferLimits>
    void execute(pattern_context<BufferLimits>& ctx, const pattern_bytecode::instruction_list& instructions)
    {
        for (const auto& instr : instructions)
        {
            switch (instr.code)
            {
            case pattern_bytecode::op_code::literal: op::literal(ctx, instr.u.literal); break;

            case pattern_bytecode::op_code::field_noalign: op::field_noalign(ctx, instr.u.field_noalign); break;
            case pattern_bytecode::op_code::field_align_left: op::field_align_left(ctx, instr.u.field_align); break;
            case pattern_bytecode::op_code::field_align_right: op::field_align_right(ctx, instr.u.field_align); break;
            case pattern_bytecode::op_code::field_align_center: op::field_align_center(ctx, instr.u.field_align); break;

            case pattern_bytecode::op_code::custom_field_noalign: op::custom_field_noalign(ctx, instr.u.custom_field_noalign); break;
            case pattern_bytecode::op_code::custom_field_align_left: op::custom_field_align_left(ctx, instr.u.custom_field_align); break;
            case pattern_bytecode::op_code::custom_field_align_right:op::custom_field_align_right(ctx, instr.u.custom_field_align); break;
            case pattern_bytecode::op_code::custom_field_align_center:op::custom_field_align_center(ctx, instr.u.custom_field_align); break;

            case pattern_bytecode::op_code::sgr: op::sgr(ctx, instr.u.sgr); break;
            case pattern_bytecode::op_code::sgr_level: op::sgr_level(ctx); break;
            }
        }
    }
}