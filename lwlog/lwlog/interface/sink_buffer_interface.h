#pragma once

#include "core.h"
#include "fwd.h"

namespace lwlog::interface
{
	class LWLOG_API sink_buffer
	{
	public:
		virtual ~sink_buffer() = default;
		virtual void add_sink(sinks::sink_ptr) = 0;
		virtual void remove_sink(sinks::sink_ptr) = 0;
		virtual std::vector<sinks::sink_ptr>& sinks() = 0;
	};
}