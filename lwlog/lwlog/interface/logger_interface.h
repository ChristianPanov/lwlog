#pragma once

#include "level_interface.h"
#include "level_filter_interface.h"
#include "pattern_interface.h"

namespace lwlog::interface
{
	class logger : public level, public level_filter, public pattern
	{
	public:
		virtual ~logger() = default;
		virtual std::string name() const = 0;

	protected:
		virtual void log(std::string_view, sink_level) = 0;
	};
}