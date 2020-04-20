#pragma once

#include "fwd.h"

namespace lwlog::interface
{
	class level_filter
	{
	public:
		virtual ~level_filter() = default;
		virtual void set_level_filter(std::initializer_list<sink_level>) = 0;
	};
}