#pragma once

#include "lwlog/sinks/sink.h"
#include "lwlog/details/stream.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stderr_sink 
		: public sink<uncolored_policy, ThreadingPolicy>
		, public details::stream
	{
	public:
		stderr_sink() : details::stream(stderr) {}
		void sink_it(std::string_view message) override 
		{
			details::stream::write(message);
		}
	};
}
