#pragma once

#include "fwd.h"

namespace lwlog::interface
{
	class sink_buffer
	{
	protected:
		~sink_buffer() = default;

	public:
		virtual void add_sink(primitives::sink_ptr) = 0;
		virtual void remove_sink(primitives::sink_ptr) = 0;
		virtual std::vector<primitives::sink_ptr>& sinks() = 0;
	};
}