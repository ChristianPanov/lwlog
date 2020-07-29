#pragma once

#include "sink.h"
#include "details/stream.h"

namespace lwlog::sinks
{
	class stdout_color_sink : public sink, public details::stream
	{
	public:
		stdout_color_sink();
		void sink_it(std::string_view message) override;
	};

	inline stdout_color_sink::stdout_color_sink()
		: details::stream(stdout)
	{}

	inline void stdout_color_sink::sink_it(std::string_view message)
	{
		details::stream::writeln(message);
	}
}