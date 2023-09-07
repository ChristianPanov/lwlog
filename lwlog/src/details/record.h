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
		record(std::string_view message, level t_level, const source_meta& meta)
			: message{ message }
			, level{ t_level }
			, meta{ meta }
		{}

		std::string_view		message;
		level					level;
		source_meta				meta;
		time_point				time_point	{};
		LWLOG_THREAD_ID_TYPE	thread_id	{ LWLOG_THREAD_ID_FN() };
		LWLOG_PROCESS_ID_TYPE	process_id	{ LWLOG_PROCESS_ID_FN() };
	};
}