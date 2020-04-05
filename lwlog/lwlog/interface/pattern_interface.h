#pragma once

#include "core.h"
#include "fwd.h"

namespace lwlog::interface
{
	class LWLOG_API pattern
	{
	public:
		virtual ~pattern() = default;
		virtual void set_pattern(std::string_view) = 0;
		virtual void add_pattern_attribute(details::pattern_attribute) = 0;
	};
}