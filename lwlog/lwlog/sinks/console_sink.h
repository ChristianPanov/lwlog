#pragma once

#include "sink.h"
#include "../core.h"

namespace lwlog::sinks
{
	class LWLOG_API console_sink : public sink
	{
	public:
		virtual ~console_sink() = default;

		void log(std::string_view message, level log_level) override;
	};
}