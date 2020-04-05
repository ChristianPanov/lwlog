#pragma once

#include "core.h"
#include "fwd.h"

namespace lwlog::interface
{
	class LWLOG_API sink
	{
	public:
		virtual ~sink() = default;
		virtual void add_sink(sinks::sink_ptr) = 0;
		virtual void remove_sink(sinks::sink_ptr) = 0;
		virtual std::vector<sinks::sink_ptr> sinks() const = 0;
	};
}