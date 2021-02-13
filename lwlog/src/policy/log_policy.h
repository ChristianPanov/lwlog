#pragma once

#include "sinks/sink.h"
#include "primitives.h"

namespace lwlog
{
	struct forward_log_policy
	{
		void log(primitives::sink_ptr sink, details::log_message log_msg);
		[[deprecated("Forward(default) logging doesn't implement that function")]]
		void sink_logs() {}
	};

	struct deferred_log_policy
	{
		void log(primitives::sink_ptr sink, details::log_message log_msg);
		void sink_logs();

	private:
		struct log_info
		{
			primitives::sink_ptr sink;
			details::log_message log_msg;
		};
		std::vector<log_info> storage;
	};

	using default_log_policy = forward_log_policy;
}