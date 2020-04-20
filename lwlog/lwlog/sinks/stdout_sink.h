#pragma once

#include "sink.h"
#include "details/stream.h"

namespace lwlog::sinks
{
	class stdout_sink : public sink, public details::stream
	{
	public:
		stdout_sink();
		void sink_it(std::string_view message) override;
	};

	inline stdout_sink::stdout_sink()
		: details::stream(stdout)
	{
		disable_color();
	}

	inline void stdout_sink::sink_it(std::string_view message)
	{
		details::stream::write(message);
	}
}