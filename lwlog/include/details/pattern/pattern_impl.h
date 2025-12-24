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
			static_cast<std::uint16_t>(m_attributes.size())
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
	void pattern<BufferLimits>::add_attribute(std::string_view flag, custom_value value)
	{
		m_attributes.emplace_back(flag, value);
		m_should_relink_custom_fields = true;
	}

	template<typename BufferLimits>
	void pattern<BufferLimits>::add_attribute(std::string_view flag, custom_value value, const custom_format_fn& fn)
	{
		m_attributes.emplace_back(flag, value, fn);
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

        auto find_index{ [&](std::uint16_t off, std::uint8_t sz) -> std::uint16_t
            {
                const std::string_view name{ src + off, sz };

                for (std::uint16_t i = 0; i < m_attributes.size(); ++i)
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
            case pattern_bytecode::op_code::custom_noalign:
                if (instr.u.custom_noalign.index == pattern_bytecode::invalid_custom_index)
                {
                    instr.u.custom_noalign.index = find_index(
                        instr.u.custom_noalign.name_offset, instr.u.custom_noalign.name_size);
                }
                break;

            case pattern_bytecode::op_code::custom_align_left:
            case pattern_bytecode::op_code::custom_align_right:
            case pattern_bytecode::op_code::custom_align_center:
                if (instr.u.custom_align.index == pattern_bytecode::invalid_custom_index)
                {
                    instr.u.custom_align.index = find_index(
                        instr.u.custom_align.name_offset, instr.u.custom_align.name_size);
                }
                break;

            default:
                break;
            }
        }

        m_should_relink_custom_fields = false;
    }
}