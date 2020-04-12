#pragma once

#include "core.h"
#include "sink.h"

namespace lwlog::sinks
{
	class LWLOG_API console_sink : public sink
	{
	public:
		void sink_it(std::string_view message) override;
	};

	inline void console_sink::sink_it(std::string_view message)
	{
		std::setvbuf(stderr, NULL, _IOFBF, 32768);
		std::fwrite((std::string(message) + "\n").data(), message.size() + 1, 1, stderr);
	}
}