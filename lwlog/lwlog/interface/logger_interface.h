#pragma once

#include "core.h"
#include "level_interface.h"
#include "sink_interface.h"
#include "backtracer_interface.h"

namespace lwlog::interface
{
	class LWLOG_API logger : public level, public sink, public backtracer
	{
	public:
		virtual ~logger() = default;
		virtual void log(std::string_view, sink_level) = 0;
		virtual void set_pattern(std::string_view) = 0;
		virtual void set_level_visibility(std::initializer_list<sink_level>) = 0;
		virtual inline std::string name() const = 0;
	};
}