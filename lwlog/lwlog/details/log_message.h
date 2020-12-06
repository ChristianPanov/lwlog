#pragma once

#include <string>

#include "fwd.h"

namespace lwlog::details
{
	class log_message
	{
	public:
		log_message() = default;
		log_message(std::string message, std::string pattern, level level);

	public:
		std::string message() const;

	private:
		std::string m_message;
		std::string m_pattern;
		level m_level{ 0 };
	};
}
