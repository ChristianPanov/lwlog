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
		stdout_sink();
		void sink_it(const details::log_message& log_msg) override;
	};

	template<typename ThreadingPolicy>
	stdout_sink<ThreadingPolicy>::stdout_sink()
		: details::stream_writer(stdout)
	{}

	template<typename ThreadingPolicy>
	void stdout_sink<ThreadingPolicy>::sink_it(const details::log_message& log_msg)
	{
		details::stream_writer::write(m_pattern.compile(log_msg));
	}
}