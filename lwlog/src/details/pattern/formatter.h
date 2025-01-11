#pragma once

#include "details/record.h"
#include "details/memory_buffer.h"

namespace lwlog::details
{
	struct formatter
	{
		static constexpr std::uint8_t attribute_buffer_size{ 32 };

		virtual ~formatter() = default;
		virtual void format(memory_buffer<>&, const record_base&) const = 0;

		template<typename T> 
		static void format_attribute(memory_buffer<>& buffer, const flag_pair& flags, T value);
		static void format_custom_attribute(memory_buffer<>& buffer, const attribute& attrib);
	};
}

#include "formatter_impl.h"