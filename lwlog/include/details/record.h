#pragma once

#include "source_meta.h"
#include "topic_registry.h"
#include "os/time_point.h"
#include "os/os.h"
#include "details/memory_buffer.h"

namespace lwlog::details
{
	template<typename BufferLimits>
	struct record
	{
		record() = default;
		record(const char* const message, level log_level, const source_meta& meta,
			const topic_registry& topics, std::uint8_t topic_index)
			: message{ message }
			, log_level{ log_level }
			, meta{ meta }
			, topics{ topics }
			, topic_index{ topic_index }
		{}

	public:
		const char* const message;
		const level log_level;
		const source_meta meta;

		const topic_registry& topics;
		const std::uint8_t topic_index{ 0 };

		const os::time_point time_point;
		const os::execution_context execution_context;
	};
}