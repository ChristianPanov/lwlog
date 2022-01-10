#pragma once

#include "lwlog/sinks/sink.h"

namespace lwlog
{
	struct forward_log_policy
	{
		void log(sink_ptr sink, const details::log_message& log_msg);
		[[deprecated("Forward(default) logging doesn't implement that function")]]
		void sink_logs() {}
	};

	struct deferred_log_policy
	{
		void log(sink_ptr sink, const details::log_message& log_msg);
		void sink_logs();

	private:
		struct log_info
		{
			sink_ptr sink;
			details::log_message log_msg;
		};
		std::vector<log_info> m_storage;
	};
}
