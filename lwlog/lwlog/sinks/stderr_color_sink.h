#pragma once

#include "sink.h"
#include "details/stream.h"

namespace lwlog::sinks
{
	class stderr_color_sink 
		: public sink<colored_policy>
		, public details::stream
	{
	public:
		stderr_color_sink() : details::stream(stderr) {}
		void sink_it(std::string_view message) override
		{
			details::stream::write(message);
		}
	};
}