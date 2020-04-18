#pragma once

#include "core.h"
#include "sink.h"
#include "details/stream.h"

namespace lwlog::sinks
{
	class LWLOG_API stderr_color_sink : public sink, public details::stream
	{
	public:
		stderr_color_sink();
		void sink_it(std::string_view message) override;
	};

	inline stderr_color_sink::stderr_color_sink()
		: details::stream(stderr)
	{}

	inline void stderr_color_sink::sink_it(std::string_view message)
	{
		details::stream::write(message);
	}
}