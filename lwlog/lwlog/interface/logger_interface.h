#pragma once

#include "level_interface.h"
#include "level_filter_interface.h"
#include "pattern_interface.h"
#include "sink_buffer_interface.h"
#include "backtracer_interface.h"

namespace lwlog::interface
{
	class logger : public level, public level_filter,
		public pattern, public sink_buffer, public backtracer
	{
		friend class registry;
	public:
		virtual ~logger() = default;
		virtual void log(std::string_view, sink_level) = 0;
		virtual std::string name() const = 0;
	};

	using logger_ptr = logger*;
}