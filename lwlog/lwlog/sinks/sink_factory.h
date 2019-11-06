#pragma once

#include "../core.h"
#include "sink.h"
#include "console_sink.h"
#include "file_sink.h"

namespace lwlog
{
	template <typename SinkPolicy>
	class LWLOG_API sink_factory
	{
	public:
		virtual ~sink_factory() = default;

		static std::unique_ptr<sinks::sink> request();
	};
}