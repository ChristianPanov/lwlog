#pragma once

#include "core.h"
#include "level_interface.h"
#include "level_visibility_interface.h"
#include "pattern_interface.h"
#include "sink_interface.h"
#include "backtracer_interface.h"

namespace lwlog::interface
{
	class LWLOG_API logger : public level, public level_visibility, 
		public pattern, public sink, public backtracer
	{
	public:
		virtual ~logger() = default;
		virtual void log(std::string_view, sink_level) = 0;
		virtual std::string name() const = 0;
	};
}