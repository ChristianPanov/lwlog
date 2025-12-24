#pragma once

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "pattern_instruction.h"
#include "compiler/parser.h"
#include "executor/execute.h"

#include "attribute.h"
#include "details/memory_buffer.h"
#include "details/record.h"

namespace lwlog::details
{
	template<typename BufferLimits>
	class pattern
	{
	public:
        const char* compile(const details::record<BufferLimits>& record);

	public:
		void set_pattern(std::string_view pattern, bool enable_color);
		void add_attribute(std::string_view flag, attrib_value value);
		void add_attribute(std::string_view flag, attrib_value value, const attrib_callback_t& fn);

	private:
		details::memory_buffer<BufferLimits::pattern> m_pattern_src;
		details::memory_buffer<BufferLimits::pattern> m_out;

		char m_conv_buffer[BufferLimits::conversion];

	private:
		std::vector<attribute> m_attributes;
		pattern_bytecode::instruction_list m_instructions;
	};
}

#include "pattern_impl.h"