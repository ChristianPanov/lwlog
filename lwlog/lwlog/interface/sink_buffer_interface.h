#pragma once

#include "fwd.h"

namespace lwlog::interface
{
	class sink_buffer
	{
	public:
		virtual ~sink_buffer() = default;
		virtual void add_sink(sinks::sink_ptr) = 0;
		virtual void remove_sink(sinks::sink_ptr) = 0;
		virtual std::vector<sinks::sink_ptr>& sinks() = 0;
	};
}