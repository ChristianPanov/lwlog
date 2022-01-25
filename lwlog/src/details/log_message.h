#pragma once

#include <thread>

#include "tweakme_macros.h"
#include "source_meta.h"
#include "datetime.h"
#include "fwd.h"

namespace lwlog::details
{
	struct log_message
	{
		log_message() = default;
		log_message(std::string_view message,
			std::string_view logger_name, level level,
			const source_meta& meta)
			: message{ message }
			, logger_name{ logger_name }
			, level{ level }
			, meta{ meta }
		{
			LWLOG_TIME_FUNC(time_point);
			thread_id = LWLOG_THREAD_ID_FUNC();
		}

		std::string_view message;
		std::string_view logger_name;
		level level{};
		LWLOG_TIME_TYPE time_point{};
		LWLOG_THREAD_ID_TYPE thread_id{};
		source_meta meta;
	};
}