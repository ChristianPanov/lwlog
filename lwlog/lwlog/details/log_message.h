#pragma once

#include <string>

#include "fwd.h"

namespace lwlog
{
	class log_message
	{
	public:
		log_message() = default;
		log_message(std::string_view message, std::string_view pattern, 
			sink_level level, bool should_color);
		std::string message() const;

	private:
		std::string m_message;
		std::string m_pattern;
		sink_level m_level{ 0 };
		bool m_should_color{ true };
	};
}
