#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stdout_sink 
		: public sink<uncolored_policy, ThreadingPolicy>
		, public details::stream_writer
	{
	public:
		stdout_sink() : details::stream_writer(stdout) {}
		void sink_it(std::string_view message) override
		{
			details::stream_writer::write(message);
		}
	};
}