#pragma once

#include "configuration.h"
#include "source_meta.h"
#include "topic_registry.h"
#include "os/time_point.h"
#include "os/os.h"
#include "details/memory_buffer.h"

namespace lwlog::details
{
	template<typename Config, typename BufferLimits>
	struct record
	{
		record() = default;
		record(const char* message, level log_level, const source_meta& meta,
			const topic_registry<typename Config::topic_t>& topics) 
			: message{ message }
			, log_level{ log_level }
			, meta{ meta }
			, topic_registry{ topics }
		{}

	public:
		level log_level;
		source_meta meta;

		const char* message;

		const os::time_point<
			typename Config::local_time_t
		> time_point{};

		const os::execution_context<
			typename Config::thread_id_t,
			typename Config::process_id_t
		> execution_context{};

		const topic_registry<
			typename Config::topic_t
		>& topic_registry;
	};
}