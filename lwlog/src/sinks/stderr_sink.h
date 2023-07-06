#pragma once

#include "sink.h"
#include "details/console_writer.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stderr_sink 
		: public sink<colored_policy, ThreadingPolicy>
		, private details::console_writer
	{
	private:
		using sink_t = sink<colored_policy, ThreadingPolicy>;

	public:
		stderr_sink();
		void sink_it(const details::record& record) override;
	};

	template<typename ThreadingPolicy>
	stderr_sink<ThreadingPolicy>::stderr_sink()
		: details::console_writer(stderr)
	{}

	template<typename ThreadingPolicy>
	void stderr_sink<ThreadingPolicy>::sink_it(const details::record& record)
	{
		sink_t::m_current_level = record.level;
		details::console_writer::write(sink_t::m_pattern.compile(record));
	}
}