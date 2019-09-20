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

		virtual void log(std::string_view message, level log_level) = 0;

		void set_level_visibility(level log_level);
		void set_pattern(std::string_view pattern);

	protected:
		std::string m_pattern;
		level m_level{ level::all };
	};
}