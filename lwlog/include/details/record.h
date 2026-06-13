#pragma once

#include "source_meta.h"
#include "topic_registry.h"
#include "os/time_point.h"
#include "os/os.h"

namespace lwlog::details
{
	struct record
	{
		record() = default;
		record(std::string_view message, level log_level, const source_meta& meta,
			const topic_registry& topics, std::uint8_t topic_index)
			: message{ message }
			, log_level{ log_level }
			, meta{ meta }
			, topics{ topics }
			, topic_index{ topic_index }
		{}

	public:
		std::string_view message;
		const level log_level;
		const source_meta meta;

		const topic_registry& topics;
		const std::uint8_t topic_index{ 0 };

		const os::time_point time_point;
		const os::execution_context execution_context;
	};
}