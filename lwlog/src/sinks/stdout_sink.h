#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stdout_sink 
		: public sink<colored_policy, ThreadingPolicy>
		, private details::stream_writer
	{
	private:
		using sink_t = sink<colored_policy, ThreadingPolicy>;

	public:
		stdout_sink();
		void sink_it(const details::record& record) override;
	};

	template<typename ThreadingPolicy>
	stdout_sink<ThreadingPolicy>::stdout_sink()
		: details::stream_writer(stdout)
	{}

	template<typename ThreadingPolicy>
	void stdout_sink<ThreadingPolicy>::sink_it(const details::record& record)
	{
		details::stream_writer::write(sink_t::m_pattern.compile(record));
	}
}