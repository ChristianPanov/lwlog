#pragma once

#include "core.h"
#include "sink.h"

namespace lwlog::sinks
{
	class LWLOG_API console_sink : public sink
	{
	public:
		console_sink();
		void sink_it(std::string_view message) override;
	};

	inline console_sink::console_sink()
	{
		std::setvbuf(stderr, NULL, _IOFBF, 32768);
	}

	inline void console_sink::sink_it(std::string_view message)
	{
		std::fwrite((std::string(message) + "\n").data(), message.size() + 1, 1, stderr);
	}
}