#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stderr_color_sink 
		: public sink<colored_policy, ThreadingPolicy>
		, public details::stream_writer
	{
	public:
		stderr_color_sink() : details::stream_writer(stderr) {}
		void sink_it(std::string_view message) override
		{
			details::stream_writer::write(message);
		}
	};
}