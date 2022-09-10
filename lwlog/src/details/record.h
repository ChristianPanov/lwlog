#pragma once

#include "tweakme_macros.h"
#include "source_meta.h"
#include "datetime.h"
#include "os.h"

namespace lwlog::details
{
	struct record
	{
		record() = default;
		record(std::string_view message, level t_level,
			const source_meta& meta)
			: message{ message }
			, level{ t_level }
			, thread_id{ LWLOG_THREAD_ID_FN() }
			, process_id{ LWLOG_PROCESS_ID_FN() }
			, meta{ meta }
		{
			LWLOG_INIT_TIME_POINT_FN(time_point);
		}

		std::string_view message;
		level level;
		LWLOG_TIME_TYPE time_point{};
		LWLOG_THREAD_ID_TYPE thread_id;
		LWLOG_PROCESS_ID_TYPE process_id;
		source_meta meta;
	};
}