#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stderr_sink 
		: public sink<colored_policy, ThreadingPolicy>
		, private details::stream_writer
	{
	private:
		using sink_t = sink<colored_policy, ThreadingPolicy>;

	public:
		stderr_sink();
		void sink_it(const details::record& record) override;
	};

	template<typename ThreadingPolicy>
	stderr_sink<ThreadingPolicy>::stderr_sink()
		: details::stream_writer(stderr)
	{}

	template<typename ThreadingPolicy>
	void stderr_sink<ThreadingPolicy>::sink_it(const details::record& record)
	{
		details::stream_writer::write(sink_t::m_pattern.compile(record));
	}
}