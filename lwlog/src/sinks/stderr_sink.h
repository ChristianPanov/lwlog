#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stderr_sink 
		: public sink<colored_policy, ThreadingPolicy>
		, public details::stream_writer
	{
	public:
		stderr_sink();
		void sink_it(const details::log_message& log_msg) override;
	};

	template<typename ThreadingPolicy>
	stderr_sink<ThreadingPolicy>::stderr_sink()
		: details::stream_writer(stderr)
	{}

	template<typename ThreadingPolicy>
	void stderr_sink<ThreadingPolicy>::sink_it(const details::log_message& log_msg)
	{
		details::stream_writer::write(m_pattern.compile(log_msg));
	}
}