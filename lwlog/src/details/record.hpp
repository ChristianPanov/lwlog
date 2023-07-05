#pragma once

#include "tweakme_macros.hpp"
#include "source_meta.hpp"
#include "datetime.hpp"
#include "os.hpp"

namespace lwlog::details
{
	struct record
	{
		record() = default;
		record(std::string_view message, level t_level, const source_meta& meta)
			: message{ message }
			, level{ t_level }
			, meta{ meta }
		{
			LWLOG_INIT_TIME_POINT_FN(time_point);
		}

		std::string_view		message;
		level					level;
		source_meta				meta;
		LWLOG_TIME_TYPE			time_point	{};
		LWLOG_THREAD_ID_TYPE	thread_id	{ LWLOG_THREAD_ID_FN() };
		LWLOG_PROCESS_ID_TYPE	process_id	{ LWLOG_PROCESS_ID_FN() };
	};
}