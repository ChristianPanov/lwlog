#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename FlushPolicy, typename ThreadingPolicy>
	class stderr_sink
		: public sink<true, ThreadingPolicy>
		, private details::stream_writer<FlushPolicy>
	{
	private:
		using sink_t = sink<true, ThreadingPolicy>;

	public:
		stderr_sink();
		void sink_it(const details::record& record) override;
	};

	template<typename FlushPolicy, typename ThreadingPolicy>
	stderr_sink<FlushPolicy, ThreadingPolicy>::stderr_sink()
		: details::stream_writer<FlushPolicy>(stderr)
	{}

	template<typename FlushPolicy, typename ThreadingPolicy>
	void stderr_sink<FlushPolicy, ThreadingPolicy>::sink_it(const details::record& record)
	{
		sink_t::m_current_level = record.log_level;
		details::stream_writer<FlushPolicy>::write(sink_t::m_pattern.compile(record));
	}
}