#pragma once

#include <vector>

#include "core.h"
#include "sinks/sink.h"

namespace lwlog::interface
{
	class LWLOG_API sink
	{
	public:
		virtual ~sink() = default;
		virtual void add_sink(lwlog::sinks::sink_ptr) = 0;
		virtual void remove_sink(lwlog::sinks::sink_ptr) = 0;
		virtual inline std::vector<lwlog::sinks::sink_ptr> sinks() const = 0;
	};
}