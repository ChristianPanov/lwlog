#pragma once

#include "fwd.h"

namespace lwlog::interface
{
	class pattern
	{
	public:
		virtual ~pattern() = default;
		virtual void set_pattern(std::string_view) = 0;
		virtual void add_pattern_attribute(details::attribute_t) = 0;
	};
}