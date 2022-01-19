#pragma once

#include <thread>

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
			datetime::init_time_point(time_point);
			thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
		}

		std::string_view message;
		std::string_view logger_name;
		level level{};
		datetime::time_point_t time_point{};
		std::size_t thread_id{};
		source_meta meta;
	};
}