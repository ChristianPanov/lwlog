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
    void field_noalign(pattern_context<BufferLimits>& ctx, const pattern_bytecode::field_noalign_payload& payload)
    {
        const auto field_data{ resolve_field<BufferLimits>(payload.id, ctx.conversion_buffer, ctx.record) };
        ctx.out.append(field_data);
    }

    template<typename BufferLimits>
    void field_align_left(pattern_context<BufferLimits>& ctx, const pattern_bytecode::field_align_payload& payload)
    {
        const auto field_data{ resolve_field<BufferLimits>(payload.id, ctx.conversion_buffer, ctx.record) };
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
        const auto field_data{ resolve_field<BufferLimits>(payload.id, ctx.conversion_buffer, ctx.record) };
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
        const auto field_data{ resolve_field<BufferLimits>(payload.id, ctx.conversion_buffer, ctx.record) };
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
    void custom_noalign(pattern_context<BufferLimits>& ctx, const pattern_bytecode::custom_noalign_payload& payload)
    {
        if (payload.index == pattern_bytecode::invalid_custom_index || payload.index >= ctx.custom_field_count)
        {
            ctx.out.append("{", 1);
            ctx.out.append(ctx.pattern_src + payload.name_offset, payload.name_size);
            ctx.out.append("}", 1);
            return;
        }

        const auto& field{ ctx.custom_fields[payload.index] };
        const auto field_size{ field.format_fn(ctx.conversion_buffer, BufferLimits::conversion) };

        ctx.out.append(ctx.conversion_buffer, field_size);
    }

    template<typename BufferLimits>
    void custom_align_left(pattern_context<BufferLimits>& ctx, const pattern_bytecode::custom_align_payload& payload)
    {
        if (payload.index == pattern_bytecode::invalid_custom_index || payload.index >= ctx.custom_field_count)
        {
            return;
        }

        const auto& field{ ctx.custom_fields[payload.index] };
        const auto field_size{ field.format_fn(ctx.conversion_buffer, BufferLimits::conversion) };

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
    void custom_align_right(pattern_context<BufferLimits>& ctx, const pattern_bytecode::custom_align_payload& payload)
    {
        if (payload.index == pattern_bytecode::invalid_custom_index || payload.index >= ctx.custom_field_count)
        {
            return;
        }

        const auto& field{ ctx.custom_fields[payload.index] };
        const auto field_size{ field.format_fn(ctx.conversion_buffer, BufferLimits::conversion) };

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
    void custom_align_center(pattern_context<BufferLimits>& ctx, const pattern_bytecode::custom_align_payload& payload)
    {
        if (payload.index == pattern_bytecode::invalid_custom_index || payload.index >= ctx.custom_field_count)
        {
            return;
        }

        const auto& field{ ctx.custom_fields[payload.index] };
        const auto field_size{ field.format_fn(ctx.conversion_buffer, BufferLimits::conversion) };

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
    void sgr_begin(pattern_context<BufferLimits>& ctx, const pattern_bytecode::sgr_payload& payload)
    {
        ctx.out.append(payload.seq, payload.size);
    }

    template<typename BufferLimits>
    void sgr_reset(pattern_context<BufferLimits>& ctx)
    {
        ctx.out.append(sgr_resolver::reset, sgr_resolver::reset_size);
    }

    template<typename BufferLimits>
    void sgr_begin_level(pattern_context<BufferLimits>& ctx)
    {
        ctx.out.append(level_details::to_color(ctx.record.log_level));
    }
}