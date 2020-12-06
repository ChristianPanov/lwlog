#pragma once

#include "fwd.h"

namespace lwlog::interface
{
	class level_filter
	{
	protected:
		~level_filter() = default;

	public:
		virtual void set_level_filter(level) = 0;
	};
}