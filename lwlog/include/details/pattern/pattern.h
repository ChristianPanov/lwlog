#pragma once

#include <string>
#include <vector>

#include "pattern_instruction.h"
#include "compiler/parser.h"
#include "executor/execute.h"

#include "custom_field.h"
#include "details/memory_buffer.h"
#include "details/record.h"

namespace lwlog::details
{
	template<typename BufferLimits>
	class pattern
	{
	public:
        std::string_view compile(const details::record<BufferLimits>& record);

	public:
		void set_pattern(std::string_view pattern, bool enable_color);
		void add_custom_field(std::string_view name, custom_value value);
		void add_custom_field(std::string_view name, custom_value value, custom_format_fn fn);

	private:
		void link_custom_fields();

	private:
		details::memory_buffer<BufferLimits::pattern> m_pattern_src;
		details::memory_buffer<BufferLimits::pattern> m_out;

		char m_conv_buffer[BufferLimits::conversion];

	private:
		std::vector<custom_field> m_custom_fields;
		pattern_bytecode::instruction_list m_instructions;
	};
}

#include "pattern_impl.h"