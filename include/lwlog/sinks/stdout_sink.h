#pragma once

#include "lwlog/sinks/sink.h"
#include "lwlog/details/stream.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stdout_sink 
		: public sink<uncolored_policy, ThreadingPolicy>
		, public details::stream
	{
	public:
		stdout_sink() : details::stream(stdout) {}
		void sink_it(std::string_view message) override
		{
			details::stream::write(message);
		}
	};
}
