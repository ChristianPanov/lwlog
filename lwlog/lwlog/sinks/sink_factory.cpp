#include "sink_factory.h"

#include <iostream>

namespace lwlog
{
	template<typename SinkPolicy>
	std::unique_ptr<sinks::sink> sink_factory<SinkPolicy>::request()
	{
		if constexpr (std::is_same_v<SinkPolicy, sinks::console_sink>)
		{
			return std::make_unique<sinks::console_sink>();
		}

		else if constexpr (std::is_same_v<SinkPolicy, sinks::file_sink>)
		{
			return std::make_unique<sinks::file_sink>();
		}
	}

	template class sink_factory<sinks::console_sink>;
	template class sink_factory<sinks::file_sink>;
}