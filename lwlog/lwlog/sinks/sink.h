#pragma once

#include "../log_level.h"
#include "../core.h"

#include <string>

namespace lwlog::sinks
{
	class LWLOG_API sink
	{
	public:
		virtual ~sink() = default;

		virtual void log(std::string_view, level) = 0;
	};
}