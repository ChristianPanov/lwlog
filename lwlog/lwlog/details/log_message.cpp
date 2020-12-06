#include "log_message.h"
#include "level.h"
#include "formatter/formatter.h"

namespace lwlog::details
{
	log_message::log_message(std::string message, std::string pattern, level level)
		: m_message{ message }
		, m_pattern{ pattern }
		, m_level{ level }
	{
		details::formatter::insert_pattern_data({
			{"{message}",		"%v", m_message},
			{"{log_level}",		"%l", level_details::to_string(m_level)},
			{"{log_level_abr}",	"%L", std::string(1, level_details::to_string(m_level)[0])}
			});
	}

	std::string log_message::message() const
	{
		return details::formatter::format(m_pattern);
	}
}