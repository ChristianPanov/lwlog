#pragma once

#include <string>

#include "../core.h"
#include "../log_level.h"

namespace lwlog::sinks
{
	class LWLOG_API sink
	{
	public:
		sink();
		virtual ~sink() = default;

		virtual void sink_it(std::string_view, level) = 0;

	public:
		void set_pattern(std::string_view pattern);

	protected:
		std::string m_pattern;
	};
}