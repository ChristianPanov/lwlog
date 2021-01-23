#pragma once

#include <thread>

#include "details/datetime.h"
#include "fwd.h"

namespace lwlog::details
{
	struct log_message
	{
		log_message() = default;
		log_message(std::string_view pattern, std::string_view message,
			std::string_view logger_name, level level)
			: message{ message }
			, pattern{ pattern }
			, logger_name{ logger_name }
			, level{ level }
		{
			datetime::init_time_point(time_point);
			thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
		}

		std::string pattern;
		std::string_view message;
		std::string_view logger_name;
		level level;
		datetime::time_point_t time_point;
		std::size_t thread_id{ 0 };
	};
}