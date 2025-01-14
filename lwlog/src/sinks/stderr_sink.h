#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename FlushPolicy, typename Config, typename BufferLimits, typename ThreadingPolicy>
	class stderr_sink
		: public sink<true, Config, BufferLimits, ThreadingPolicy>
		, private details::stream_writer<FlushPolicy>
	{
	private:
		using sink_t = sink<true, Config, BufferLimits, ThreadingPolicy>;

	public:
		stderr_sink();
		void sink_it(const details::record<Config, BufferLimits>& record) override;
	};

	template<typename FlushPolicy, typename Config, typename BufferLimits, typename ThreadingPolicy>
	stderr_sink<FlushPolicy, Config, BufferLimits, ThreadingPolicy>::stderr_sink()
		: details::stream_writer<FlushPolicy>(stderr)
	{}

	template<typename FlushPolicy, typename Config, typename BufferLimits, typename ThreadingPolicy>
	void stderr_sink<FlushPolicy, Config, BufferLimits, ThreadingPolicy>::sink_it(const details::record<Config, BufferLimits>& record)
	{
		sink_t::m_current_level = record.log_level;
		details::stream_writer<FlushPolicy>::write(sink_t::m_pattern.compile(record));
	}
}