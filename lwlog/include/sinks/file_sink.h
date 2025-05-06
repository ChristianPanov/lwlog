#pragma once

#include "sink.h"
#include "details/stream_writer.h"

namespace lwlog::sinks
{
	template<typename FlushPolicy, typename BufferLimits, typename ThreadingPolicy>
	class file_sink 
		: public sink<false, BufferLimits, ThreadingPolicy>
		, private details::stream_writer<FlushPolicy>
	{
	private:
		using sink_t = sink<false, BufferLimits, ThreadingPolicy>;

	public:
		file_sink() = default;
		explicit file_sink(std::string_view path);

	public:
		void sink_it(const details::record<BufferLimits>& record) override;
	};

	template<typename FlushPolicy, typename BufferLimits, typename ThreadingPolicy>
	file_sink<FlushPolicy, BufferLimits, ThreadingPolicy>::file_sink(std::string_view path)
		: details::stream_writer<FlushPolicy>(path)
	{}

	template<typename FlushPolicy, typename BufferLimits, typename ThreadingPolicy>
	void file_sink<FlushPolicy, BufferLimits, ThreadingPolicy>::sink_it(const details::record<BufferLimits>& record)
	{
		sink_t::m_current_level = record.log_level;
		details::stream_writer<FlushPolicy>::write(sink_t::m_pattern.compile(record));
		sink_t::m_pattern.reset_pattern();
	}
}