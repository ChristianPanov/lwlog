#pragma once

#include "../core.h"
#include "sink.h"

namespace lwlog::sinks
{
	class LWLOG_API console_sink : public sink
	{
	public:
		virtual ~console_sink() = default;

		virtual void sink_it(std::string_view message) override;
	};
}