#pragma once

#include "fwd.h"

namespace lwlog::interface
{
	class sink_buffer
	{
	public:
		virtual ~sink_buffer() = default;
		virtual void add_sink(primitives::sink_ptr) = 0;
		virtual void remove_sink(primitives::sink_ptr) = 0;
		virtual std::vector<primitives::sink_ptr>& sinks() = 0;
	};
}