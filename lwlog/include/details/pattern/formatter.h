#pragma once

#include "details/record.h"
#include "details/memory_buffer.h"

namespace lwlog::details
{
	template<typename BufferLimits>
	struct formatter
	{
		virtual ~formatter() = default;
		virtual void format(details::memory_buffer<BufferLimits::pattern>&, char*, const record<BufferLimits>&) const = 0;

		template<typename T> 
		static void format_attribute(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, 
			char* conv_buffer, const flag_pair& flags, const T& value);
		static void format_custom_attribute(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, 
			char* conv_buffer, const attribute& attrib);
	};
}

#include "formatter_impl.h"