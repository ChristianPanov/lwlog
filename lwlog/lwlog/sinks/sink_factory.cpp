#include "sink_factory.h"

#include <iostream>

namespace lwlog
{
	template<typename SinkPolicy>
	std::unique_ptr<sinks::sink> sink_factory<SinkPolicy>::request()
	{
		return std::make_unique<SinkPolicy>();
	}

	template class sink_factory<sinks::console_sink>;
	template class sink_factory<sinks::file_sink>;
}