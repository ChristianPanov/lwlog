#pragma once

#include "pattern.h"

namespace lwlog::details
{
	template<typename BufferLimits>
	const char* pattern<BufferLimits>::compile(const details::record<BufferLimits>& record)
	{
        m_out.reset();

		pattern_executor::pattern_context<BufferLimits> ctx{ 
			m_out, 
			record,
			m_pattern_src.c_str(),
			m_conv_buffer
		};

		pattern_executor::execute(ctx, m_instructions);

		//for (const auto& attribute : m_attributes)
		//	formatter<BufferLimits>::format_custom_attribute(m_pattern_buffer, m_conv_buffer, attribute);

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
	}

	template<typename BufferLimits>
	void pattern<BufferLimits>::add_attribute(std::string_view flag, attrib_value value)
	{
		m_attributes.emplace_back(flag, value);
	}

	template<typename BufferLimits>
	void pattern<BufferLimits>::add_attribute(std::string_view flag, attrib_value value, const attrib_callback_t& fn)
	{
		m_attributes.emplace_back(flag, value, fn);
	}
}