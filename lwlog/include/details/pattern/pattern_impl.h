#pragma once

#include "pattern.h"

namespace lwlog::details
{
	template<typename BufferLimits>
	const char* pattern<BufferLimits>::compile(const details::record<BufferLimits>& record)
	{
		this->link_custom_fields_if_needed();

        m_out.reset();

		pattern_executor::pattern_context<BufferLimits> ctx{ 
			m_out, 
			record,
			m_pattern_src.c_str(),
			m_conv_buffer,
			m_attributes.data(),
			m_attributes.size()
		};

		pattern_executor::execute(ctx, m_instructions);

		return m_out.c_str();
	}

	template<typename BufferLimits>
	void pattern<BufferLimits>::set_pattern(std::string_view pattern, bool enable_color)
	{
		m_instructions.clear();
		m_pattern_src.reset();

		m_pattern_src.append(pattern);
		m_pattern_src.append('\n');

		pattern_compiler::parser parser;
		parser.init(m_pattern_src.c_str(), m_pattern_src.size(), enable_color);
		parser.parse_sequence(m_instructions);

		m_should_relink_custom_fields = true;
	}

	template<typename BufferLimits>
	void pattern<BufferLimits>::add_custom_field(std::string_view name, custom_value value)
	{
		m_attributes.emplace_back(name, value);
		m_should_relink_custom_fields = true;
	}

	template<typename BufferLimits>
	void pattern<BufferLimits>::add_custom_field(std::string_view name, custom_value value, const custom_format_fn& fn)
	{
		m_attributes.emplace_back(name, value, fn);
		m_should_relink_custom_fields = true;
	}

    template<typename BufferLimits>
    void pattern<BufferLimits>::link_custom_fields_if_needed()
    {
        if (!m_should_relink_custom_fields)
        {
            return;
        }

        const char* src{ m_pattern_src.c_str() };

        auto find_index{ [&](std::uint16_t offset, std::uint8_t size) -> std::uint8_t
            {
                const std::string_view name{ src + offset, size };

                for (std::size_t i = 0; i < m_attributes.size(); ++i)
                {
                    if (m_attributes[i].name == name)
                    {
                        return i;
                    }
                }
                return pattern_bytecode::invalid_custom_index;
            } };

        for (auto& instr : m_instructions)
        {
            switch (instr.code)
            {
            case pattern_bytecode::op_code::custom_field_noalign:
            {
                auto& payload{ instr.u.custom_field_noalign };
                payload.index = find_index(payload.name_offset, payload.name_size);

                if (payload.index == pattern_bytecode::invalid_custom_index)
                {
                    const auto field_offset{ payload.field_offset };
                    const auto field_size{ payload.field_size };

                    instr.code = pattern_bytecode::op_code::literal;
                    instr.u.literal = { field_offset, field_size };
                }
                break;
            }

            case pattern_bytecode::op_code::custom_field_align_left:
            case pattern_bytecode::op_code::custom_field_align_right:
            case pattern_bytecode::op_code::custom_field_align_center:
            {
                auto& payload{ instr.u.custom_field_align };
                payload.index = find_index(payload.name_offset, payload.name_size);

                if (payload.index == pattern_bytecode::invalid_custom_index)
                {
                    const auto field_offset{ payload.field_offset };
                    const auto field_size{ payload.field_size };

                    instr.code = pattern_bytecode::op_code::literal;
                    instr.u.literal = { field_offset, field_size };
                }
                break;
            }
            }
        }

        m_should_relink_custom_fields = false;
    }
}