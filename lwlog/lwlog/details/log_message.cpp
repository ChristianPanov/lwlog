#include "log_message.h"
#include "sinks/sink_level.h"
#include "formatter.h"

namespace lwlog
{
	log_message::log_message(std::string message, std::string pattern,
		sink_level level, bool should_color)
		: m_message{ message }, m_pattern{ pattern }
		, m_level{ level }, m_should_color{ should_color }
	{}

	std::string log_message::message() const
	{
		details::formatter::insert_pattern_data({
			{"{message}",		"%v", m_message},
			{"{log_level}",		"%l", level_to_string()},
			{"{log_level_abr}",	"%L", std::string(1, level_to_string()[0])}
			});

		return details::formatter::format(m_pattern, m_should_color);
	}

	std::string log_message::level_to_string() const
	{
		if (m_level == sink_level::info) { return "info"; }
		else if (m_level == sink_level::warning) { return "warning"; }
		else if (m_level == sink_level::error) { return "error"; }
		else if (m_level == sink_level::critical) { return "critical"; }
		else if (m_level == sink_level::debug) { return "debug"; }
	}

	void log_message::disable_color()
	{
		m_should_color = false;
	}

	bool log_message::should_color() const
	{
		return m_should_color;
	}
}