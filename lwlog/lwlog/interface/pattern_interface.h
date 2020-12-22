#pragma once

#include "fwd.h"

namespace lwlog::interface
{
	class pattern
	{
	protected:
		~pattern() = default;

	public:
		virtual void set_pattern(std::string_view) = 0;
	};
}