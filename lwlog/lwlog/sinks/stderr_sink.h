#pragma once

#include "sink.h"
#include "details/stream.h"

namespace lwlog::sinks
{
	class stderr_sink 
		: public sink<uncolored_policy>
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