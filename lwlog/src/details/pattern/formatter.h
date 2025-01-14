#pragma once

#include "details/record.h"
#include "details/memory_buffer.h"

namespace lwlog::details
{
	template<typename Config, typename BufferLimits>
	struct formatter
	{
		virtual ~formatter() = default;
		virtual void format(memory_buffer<BufferLimits::pattern>&, const record<Config, BufferLimits>&) const = 0;

		template<typename T> 
		static void format_attribute(memory_buffer<BufferLimits::pattern>& buffer, const flag_pair& flags, T value);
		static void format_custom_attribute(memory_buffer<BufferLimits::pattern>& buffer, const attribute& attrib);
	};
}

#include "formatter_impl.h"