#pragma once

#include <string>

#include "core.h"

namespace lwlog
{
	enum class sink_level;
	class LWLOG_API  logger_interface
	{
	public:
		virtual void log(std::string_view, sink_level) = 0;
		virtual void set_pattern(std::string_view) = 0;
		virtual void set_level_visibility(std::initializer_list<sink_level>) = 0;
	};
}