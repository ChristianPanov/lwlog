#pragma once

#include <string>

#include "core.h"
#include "details/color.h"
#include "fwd.h"

namespace lwlog
{
	class LWLOG_API log_message
	{
	public:
		log_message() = default;
		log_message(std::string message, std::string pattern,
			sink_level level, bool should_color);

		std::string message() const;
		std::string level_to_string() const;

		void disable_color();
		bool should_color() const;

	private:
		std::string m_message;
		std::string m_pattern{ "[%d, %T] [%l] [%n]: %v" };
		sink_level m_level{ 0 };
		bool m_should_color{ true };
	};
}
