#pragma once

#include "sink.h"
#include "details/stream.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stdout_color_sink
		: public sink<colored_policy, ThreadingPolicy>
		, public details::stream
	{
	public:
		stdout_color_sink() : details::stream(stdout) {}
		void sink_it(std::string_view message) override
		{
			details::stream::write(message);
		}
	};
}