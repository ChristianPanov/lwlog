#pragma once

#include "log_level_interface.h"
#include "level_filter_interface.h"
#include "pattern_interface.h"

namespace lwlog::interface
{
	class logger : public log_level, public level_filter, public pattern
	{
	public:
		virtual ~logger() = default;
		virtual void sink_logs() = 0;
		virtual std::string name() const = 0;

	protected:
		virtual void log(std::string_view, level) = 0;
	};
}