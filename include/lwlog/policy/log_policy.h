#pragma once

#include "lwlog/sinks/sink.h"
#include "lwlog/primitives.h"

namespace lwlog
{
	struct forward_log_policy
	{
		void log(primitives::sink_ptr t_sink, std::string_view message, level t_level);
		void init_attributes(std::string_view message, level t_level);
		[[deprecated("Forward(default) logging doesn't implement that function")]] 
		void sink_logs() {}
	};

	struct deferred_log_policy
	{
		void log(primitives::sink_ptr t_sink, std::string_view t_message, level t_level);
		void init_attributes(std::string_view message, level t_level) {}
		void sink_logs();

	private:
		struct log_info 
		{
			primitives::sink_ptr sink;
			std::string message;
			std::string pattern;
			level t_level;
		};
		std::vector<log_info> storage;
	};

	using default_log_policy = forward_log_policy;
}
