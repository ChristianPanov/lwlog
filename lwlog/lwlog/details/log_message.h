#pragma once

#include <string>

#include "fwd.h"

namespace lwlog::details
{
	struct log_message_t
	{
		std::string message;
		std::string pattern;
		sink_level level{ 0 };
		bool should_color{ true };
	};

	class log_message
	{
	public:
		log_message() = default;
		log_message(log_message_t t_log_message);

	public:
		std::string message() const;

	private:
		log_message_t m_log_message;
	};
}
