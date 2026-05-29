#pragma once

#include "context.h"
#include "field_resolver.h"
#include "details/pattern/pattern_instruction.h"
#include "details/terminal/sgr_table.h"

namespace lwlog::details::pattern_executor::op
{
    template<typename BufferLimits>
    void literal(pattern_context<BufferLimits>& ctx, const pattern_bytecode::literal_payload& payload)
    {
        ctx.out.append(ctx.pattern_src + payload.offset, payload.size);
    }

    template<typename BufferLimits>
    void field_noalign(pattern_context<BufferLimits>& ctx, const pattern_bytecode::field_noalign_payload& payload)
    {
        const auto field_data{ resolve_field<BufferLimits>(payload.field, ctx.conversion_buffer, ctx.log_record) };
        ctx.out.append(field_data);
    }

    template<typename BufferLimits>
    void field_align_left(pattern_context<BufferLimits>& ctx, const pattern_bytecode::field_align_payload& payload)
    {
        const auto field_data{ resolve_field<BufferLimits>(payload.field, ctx.conversion_buffer, ctx.log_record) };
        const auto field_size{ field_data.size() };

        if (payload.width <= field_size)
        {
            ctx.out.append(field_data);
            return;
        }

        const std::size_t padding_size{ payload.width - field_size };

        ctx.out.append(field_data);
        ctx.out.append(payload.fill_char, padding_size);
    }

    template<typename BufferLimits>
    void field_align_right(pattern_context<BufferLimits>& ctx, const pattern_bytecode::field_align_payload& payload)
    {
        const auto field_data{ resolve_field<BufferLimits>(payload.field, ctx.conversion_buffer, ctx.log_record) };
        const auto field_size{ field_data.size() };

        if (payload.width <= field_size)
        {
            ctx.out.append(field_data);
            return;
        }

        const std::size_t padding_size{ payload.width - field_size };

        ctx.out.append(payload.fill_char, padding_size);
        ctx.out.append(field_data);
    }

    template<typename BufferLimits>
    void field_align_center(pattern_context<BufferLimits>& ctx, const pattern_bytecode::field_align_payload& payload)
    {
        const auto field_data{ resolve_field<BufferLimits>(payload.field, ctx.conversion_buffer, ctx.log_record) };
        const auto field_size{ field_data.size() };

        if (payload.width <= field_size)
        {
            ctx.out.append(field_data);
            return;
        }

        const std::size_t padding_size{ payload.width - field_size };

        const std::size_t left{ padding_size / 2 };
        const std::size_t right{ padding_size - left };

        ctx.out.append(payload.fill_char, left);
        ctx.out.append(field_data);
        ctx.out.append(payload.fill_char, right);
    }

    template<typename BufferLimits>
    void custom_field_noalign(pattern_context<BufferLimits>& ctx, const pattern_bytecode::custom_field_noalign_payload& payload)
    {
        const auto& field{ ctx.custom_fields[payload.index] };
        const auto field_size{ field.format_fn(field.value, ctx.conversion_buffer, BufferLimits::conversion) };

        ctx.out.append(ctx.conversion_buffer, field_size);
    }

    template<typename BufferLimits>
    void custom_field_align_left(pattern_context<BufferLimits>& ctx, const pattern_bytecode::custom_field_align_payload& payload)
    {
        const auto& field{ ctx.custom_fields[payload.index] };
        const auto field_size{ field.format_fn(field.value, ctx.conversion_buffer, BufferLimits::conversion) };

        if (payload.width <= field_size)
        {
            ctx.out.append(ctx.conversion_buffer, field_size);
            return;
        }

        const std::size_t padding_size{ payload.width - field_size };

        ctx.out.append(ctx.conversion_buffer, field_size);
        ctx.out.append(payload.fill_char, padding_size);
    }

    template<typename BufferLimits>
    void custom_field_align_right(pattern_context<BufferLimits>& ctx, const pattern_bytecode::custom_field_align_payload& payload)
    {
        const auto& field{ ctx.custom_fields[payload.index] };
        const auto field_size{ field.format_fn(field.value, ctx.conversion_buffer, BufferLimits::conversion) };

        if (payload.width <= field_size)
        {
            ctx.out.append(ctx.conversion_buffer, field_size);
            return;
        }

        const std::size_t padding_size{ payload.width - field_size };

        ctx.out.append(payload.fill_char, padding_size);
        ctx.out.append(ctx.conversion_buffer, field_size);
    }

    template<typename BufferLimits>
    void custom_field_align_center(pattern_context<BufferLimits>& ctx, const pattern_bytecode::custom_field_align_payload& payload)
    {
        const auto& field{ ctx.custom_fields[payload.index] };
        const auto field_size{ field.format_fn(field.value, ctx.conversion_buffer, BufferLimits::conversion) };

        if (payload.width <= field_size)
        {
            ctx.out.append(ctx.conversion_buffer, field_size);
            return;
        }

        const std::size_t padding_size{ payload.width - field_size };

        const std::size_t left{ padding_size / 2 };
        const std::size_t right{ padding_size - left };

        ctx.out.append(payload.fill_char, left);
        ctx.out.append(ctx.conversion_buffer, field_size);
        ctx.out.append(payload.fill_char, right);
    }

    template<typename BufferLimits>
    void sgr(pattern_context<BufferLimits>& ctx, const pattern_bytecode::sgr_payload& payload)
    {
        const auto& entry{ terminal::sgr_table[payload.code] };
        ctx.out.append(entry.seq, entry.size);
    }

    template<typename BufferLimits>
    void sgr_level(pattern_context<BufferLimits>& ctx)
    {
        ctx.out.append(level_details::to_color(ctx.log_record.log_level));
    }
}