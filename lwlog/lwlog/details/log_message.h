#pragma once

#include <string>

#include "core.h"
#include "fwd.h"
#include "details/color.h"

namespace lwlog
{
	class LWLOG_API log_message
	{
	public:
		log_message() = default;
		log_message(std::string_view message, std::string_view pattern,
			sink_level level, bool should_color);

		std::string data() const;

	private:
		std::string level_to_string() const;

	private:
		std::string m_message;
		std::string m_pattern;
		sink_level m_level{ 0 };
		bool m_should_color{ true };
	};
}
