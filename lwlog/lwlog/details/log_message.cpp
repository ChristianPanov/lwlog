#include "log_message.h"
#include "sinks/sink_level.h"
#include "formatter.h"

namespace lwlog
{
	log_message::log_message(std::string_view message, std::string_view pattern,
		sink_level level, bool should_color)
		: m_message{ message }, m_pattern{ pattern }
		, m_level{ level }, m_should_color{ should_color }
	{}

	std::string log_message::message() const
	{
		details::formatter::insert_pattern_data({
			{"{message}",		"%v", m_message},
			{"{log_level}",		"%l", level_to_string(m_level)},
			{"{log_level_abr}",	"%L", std::string(1, level_to_string(m_level)[0])}
			});

		return details::formatter::format(m_pattern, m_should_color);
	}
}