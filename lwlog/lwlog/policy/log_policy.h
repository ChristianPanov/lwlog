#pragma once

#include "sinks/sink.h"
#include "primitives.h"

namespace lwlog
{
	struct forward_log_policy
	{
		void log(primitives::sink_ptr t_sink, std::string_view message, level t_level);
		void init_attributes(std::string_view message, level t_level);
		void flush_logs() {};
	};

	struct deferred_log_policy
	{
		void log(primitives::sink_ptr t_sink, std::string_view t_message, level t_level);
		void init_attributes(std::string_view message, level t_level) {};
		void flush_logs();

	private:
		struct log_info;
		std::vector<log_info> storage;
	};

	using default_log_policy = forward_log_policy;
}