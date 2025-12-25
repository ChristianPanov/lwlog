#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename BufferLimits, typename FlushPolicy, typename ThreadingPolicy>
	class stdout_sink 
		: public sink<true, BufferLimits, ThreadingPolicy>
		, private details::stream_writer<FlushPolicy>
	{
	private:
		using sink_t = sink<true, BufferLimits, ThreadingPolicy>;

	public:
		stdout_sink();
		void sink_it(const details::record<BufferLimits>& record) override;
		void sink_it(std::string_view message) override;
	};

	template<typename BufferLimits, typename FlushPolicy, typename ThreadingPolicy>
	stdout_sink<BufferLimits, FlushPolicy, ThreadingPolicy>::stdout_sink()
		: details::stream_writer<FlushPolicy>(stdout)
	{}

	template<typename BufferLimits, typename FlushPolicy, typename ThreadingPolicy>
	void stdout_sink<BufferLimits, FlushPolicy, ThreadingPolicy>::sink_it(const details::record<BufferLimits>& record)
	{
		sink_t::m_current_level = record.log_level;
		details::stream_writer<FlushPolicy>::write(sink_t::m_pattern.compile(record));
		sink_t::m_pattern.reset_pattern();
	}

	template<typename BufferLimits, typename FlushPolicy, typename ThreadingPolicy>
	void stdout_sink<BufferLimits, FlushPolicy, ThreadingPolicy>::sink_it(std::string_view message)
	{
		details::stream_writer<FlushPolicy>::write(message);
	}
}