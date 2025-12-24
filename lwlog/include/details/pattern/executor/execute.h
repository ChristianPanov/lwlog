#pragma once

#include "context.h"
#include "ops.h"
#include "details/pattern/pattern_instruction.h"

namespace lwlog::details::pattern_executor
{
    template<typename BufferLimits>
    static void execute(pattern_context<BufferLimits>& ctx, const pattern_bytecode::instruction_list& instructions)
    {
        for (const auto& instr : instructions)
        {
            switch (instr.code)
            {
            case pattern_bytecode::op_code::literal: op::literal(ctx, instr.u.literal); break;
            case pattern_bytecode::op_code::field: op::field(ctx, instr.u.field); break;
            case pattern_bytecode::op_code::sgr_begin: op::sgr_begin(ctx, instr.u.sgr); break;
            case pattern_bytecode::op_code::sgr_reset: op::sgr_reset(ctx); break;
            }
        }
    }
}