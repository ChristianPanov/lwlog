#pragma once

#include "sinks/sink.h"

namespace lwlog
{
	struct forward_log_policy
	{
		static void log(sink_ptr sink, const details::record& record);
		[[deprecated("Forward(default) logging doesn't implement that function")]]
		static void sink_logs() {}
	};

	struct deferred_log_policy
	{
		static void log(sink_ptr sink, const details::record& record);
		static void sink_logs();

	private:
		struct log_info
		{
			sink_ptr sink;
			details::record record;
		};
		static std::vector<log_info> m_storage;
	};
}