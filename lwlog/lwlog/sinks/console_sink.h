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
		fwrite((std::string(message) + "\n").data(), message.size() + 1, 1, stderr);
	}
}