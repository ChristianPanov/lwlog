#pragma once

#include "../core.h"
#include "sink.h"

namespace lwlog::sinks
{
	class LWLOG_API console_sink : public virtual sink
	{
	public:
		virtual ~console_sink() = default;

		void sink_it(std::string_view message, level log_level) override;
	};
}