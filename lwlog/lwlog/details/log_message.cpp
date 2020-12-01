#include "log_message.h"
#include "level.h"
#include "formatter/formatter.h"

namespace lwlog::details
{
	log_message::log_message(log_message_t t_log_message)
		: m_log_message { t_log_message }
	{
		details::formatter::insert_pattern_data({
			{"{message}",		"%v", m_log_message.message},
			{"{log_level}",		"%l", level::level_to_string(m_log_message.level)},
			{"{log_level_abr}",	"%L", std::string(1, level::level_to_string(m_log_message.level)[0])}
			});
	}

	std::string log_message::message() const
	{
		return details::formatter::format(m_log_message.pattern);
	}
}