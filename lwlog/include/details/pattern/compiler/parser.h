#pragma once

#include <cstddef>

#include "details/pattern/pattern_instruction.h"
#include "details/sgr_resolver.h"

namespace lwlog::details::pattern_compiler
{
    enum class field_type : std::uint8_t
    {
        builtin,
        custom,
        literal,
        error
    };

    class parser
    {
    public:
        void init(const char* src, std::size_t size, bool enable_color);
        bool parse_sequence(pattern_bytecode::instruction_list& out, char until = '\0', bool allow_color = true);

    private:
        void emit_literal_instruction(pattern_bytecode::instruction_list& out, std::uint16_t offset, std::uint16_t size);
        void emit_field_instruction(pattern_bytecode::instruction_list& out, pattern_bytecode::builtin_field field,
            const pattern_bytecode::alignment_info& alignment);
        void emit_custom_instruction(pattern_bytecode::instruction_list& out, 
            std::uint16_t field_offset, std::uint16_t field_size,
            std::uint16_t name_offset, std::uint8_t name_size, const pattern_bytecode::alignment_info& alignment);
        void emit_sgr_begin_instruction(pattern_bytecode::instruction_list& out, std::uint8_t code);
        void emit_sgr_end_instruction(pattern_bytecode::instruction_list& out);
        void emit_sgr_begin_level_instruction(pattern_bytecode::instruction_list& out);

        void flush_pending_literal(pattern_bytecode::instruction_list& out, std::size_t literal_end_offset);

    private:
        bool recover_field_as_literal(pattern_bytecode::instruction_list& out);
        field_type parse_field_short_alias(pattern_bytecode::builtin_field& out);
        field_type parse_field_name(pattern_bytecode::builtin_field& out_id,
            std::uint16_t& out_name_offset, std::uint8_t& out_name_size);
        bool parse_alignment_specs(pattern_bytecode::alignment_info& out);
        bool parse_color(pattern_bytecode::instruction_list& out);
        bool parse_field(pattern_bytecode::instruction_list& out);

    private:
        static bool lookup_field_short_alias(char ch, pattern_bytecode::builtin_field& out);
        static bool lookup_field_name(std::string_view name, pattern_bytecode::builtin_field& out);

        static constexpr bool is_digit(char c);
        static constexpr bool is_align(char c);

    private:
        const char* m_src{ nullptr };
        std::size_t m_size{ 0 };

        std::size_t m_pos{ 0 };
        std::size_t m_pending_literal_begin{ 0 };

        bool m_enable_color{ false };
    };
}