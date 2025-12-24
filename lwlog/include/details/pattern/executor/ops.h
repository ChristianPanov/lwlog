#pragma once

#include "context.h"
#include "field_resolver.h"
#include "details/pattern/pattern_instruction.h"
#include "details/sgr_resolver.h"

namespace lwlog::details::pattern_executor::op
{
    template<typename BufferLimits>
    void literal(pattern_context<BufferLimits>& ctx, const pattern_bytecode::literal_payload& payload)
    {
        ctx.out.append(ctx.pattern_src + payload.offset, payload.size);
    }

    template<typename BufferLimits>
    void field(pattern_context<BufferLimits>& ctx, const pattern_bytecode::field_payload& payload)
    {
        const auto field_data{ resolve_field<BufferLimits>(payload.id, ctx.conversion_buffer, ctx.record) };
        const auto field_size{ field_data.size() };

        if (payload.align.width == 0 || payload.align.width <= field_size)
        {
            ctx.out.append(field_data);

            return;
        }

        const std::size_t padding_size{ payload.align.width - field_size };

        if (payload.align.side_char == '<')
        {
            ctx.out.append(field_data);
            ctx.out.append(payload.align.fill_char, padding_size);
        }
        else if (payload.align.side_char == '>')
        {
            ctx.out.append(payload.align.fill_char, padding_size);
            ctx.out.append(field_data);
        }
        else
        {
            const std::size_t left{ padding_size / 2 };
            const std::size_t right{ padding_size - left };

            ctx.out.append(payload.align.fill_char, left);
            ctx.out.append(field_data);
            ctx.out.append(payload.align.fill_char, right);
        }
    }

    template<typename BufferLimits>
    void sgr_begin(pattern_context<BufferLimits>& ctx, const pattern_bytecode::sgr_payload& payload)
    {
        ctx.out.append(payload.seq, payload.size);
    }

    template<typename BufferLimits>
    void sgr_reset(pattern_context<BufferLimits>& ctx)
    {
        ctx.out.append(sgr_resolver::reset, sgr_resolver::reset_size);
    }
}