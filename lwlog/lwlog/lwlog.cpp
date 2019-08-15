#include "lwlog.h"
#include "formatter.h"

namespace lwlog
{
	logger::logger(std::string_view logger_name)
		: m_loggerName(logger_name), m_pattern("[%d, %x] [%l] [%n]: %v"), 
		m_logLevelVisibility(log_level::all)
	{
		if (registry::is_registry_automatic() == true)
		{
			registry::register_logger(*this);
		}

		formatter::update_pattern_data("%n", m_loggerName);
	}

	void logger::set_logLevel_visibility(log_level logLevel)
	{
		if (logLevel == log_level::all)
		{
			m_logLevelVisibility = log_level::info | log_level::warning | log_level::error
				| log_level::critical | log_level::debug;
		}
		else if (logLevel == log_level::none)
		{
			m_logLevelVisibility = log_level::none;
		}
		else
		{
			m_logLevelVisibility = logLevel;
		}
	}

	void logger::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}

	void logger::info(std::string_view message)
	{
		m_message = message;
		m_logLevel = "info";

		formatter::update_pattern_data("%v", message);
		formatter::update_pattern_data("%L", std::string(1, toupper(m_logLevel[0])));
		formatter::update_pattern_data("%l", m_logLevel);

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::info))
		{
			lwlog::print("{0} \n", formatter::format(m_message, m_pattern));
		}
	}

	void logger::warning(std::string_view message)
	{
		m_message = message;
		m_logLevel = "warning";

		formatter::update_pattern_data("%v", message);
		formatter::update_pattern_data("%L", std::string(1, toupper(m_logLevel[0])));
		formatter::update_pattern_data("%l", m_logLevel);

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::warning))
		{
			lwlog::print("{0} \n", formatter::format(m_message, m_pattern));
		}
	}

	void logger::error(std::string_view message)
	{
		m_message = message;
		m_logLevel = "error";

		formatter::update_pattern_data("%v", message);
		formatter::update_pattern_data("%L", std::string(1, toupper(m_logLevel[0])));
		formatter::update_pattern_data("%l", m_logLevel);

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::error))
		{
			lwlog::print("{0} \n", formatter::format(m_message, m_pattern));
		}
	}

	void logger::critical(std::string_view message)
	{
		m_message = message;
		m_logLevel = "critical";

		formatter::update_pattern_data("%v", message);
		formatter::update_pattern_data("%L", std::string(1, toupper(m_logLevel[0])));
		formatter::update_pattern_data("%l", m_logLevel);

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::critical))
		{
			lwlog::print("{0} \n", formatter::format(m_message, m_pattern));
		}
	}

	void logger::debug(std::string_view message)
	{
		m_message = message;
		m_logLevel = "debug";

		formatter::update_pattern_data("%v", message);
		formatter::update_pattern_data("%L", std::string(1, toupper(m_logLevel[0])));
		formatter::update_pattern_data("%l", m_logLevel);

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::debug))
		{
			lwlog::print("{0} \n", formatter::format(m_message, m_pattern));
		}
	}
}
