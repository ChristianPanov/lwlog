#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stdout_sink 
		: public sink<colored_policy, ThreadingPolicy>
		, public details::stream_writer
	{
	public:
		stdout_sink() : details::stream_writer(stdout) {}
		void sink_it(const details::log_message& log_msg) override
		{
			details::stream_writer::write(m_pattern.compile(log_msg));
		}
	};
}