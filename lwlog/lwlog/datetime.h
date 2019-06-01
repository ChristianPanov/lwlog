#pragma once

#include <chrono>
#include <sstream>
#include <iomanip>
#include <thread>
#include <ctime>

namespace lwlog
{
	namespace datetime
	{
		static std::string get_current_time_and_date(const char* format)
		{
			auto now = std::chrono::system_clock::now();
			auto in_time_t = std::chrono::system_clock::to_time_t(now);

			std::stringstream ss;
			ss << std::put_time(std::localtime(&in_time_t), format);
			return ss.str();
		}

		static std::string get_current_time()
		{
			return get_current_time_and_date("%X");
		}

		static std::string get_current_date()
		{
			return get_current_time_and_date("%Y-%m-%d");
		}
	}
}
