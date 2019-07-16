#include "lwlog.h"

namespace lwlog
{
	logger::logger(std::string_view logger_name)
		: m_loggerName(logger_name), m_pattern("[%d, %X] [%l] [%n]: %v"), 
		m_logLevelVisibility(log_level::all)
	{
		if (registry::is_registry_automatic() == true)
		{
			registry::register_logger(*this);
		}
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

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::info))
		{
			lwlog::print("{0} \n", format(m_message, m_pattern));
		}
	}

	void logger::warning(std::string_view message)
	{
		m_message = message;
		m_logLevel = "warning";

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::warning))
		{
			lwlog::print("{0} \n", format(m_message, m_pattern));
		}
	}

	void logger::error(std::string_view message)
	{
		m_message = message;
		m_logLevel = "error";

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::error))
		{
			lwlog::print("{0} \n", format(m_message, m_pattern));
		}
	}

	void logger::critical(std::string_view message)
	{
		m_message = message;
		m_logLevel = "critical";

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::critical))
		{
			lwlog::print("{0} \n", format(m_message, m_pattern));
		}
	}

	void logger::debug(std::string_view message)
	{
		m_message = message;
		m_logLevel = "debug";

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::debug))
		{
			lwlog::print("{0} \n", format(m_message, m_pattern));
		}
	}

	std::string logger::format(std::string_view message, std::string pattern)
	{
		m_patternsData.emplace("%A", datetime::get_weekday_abbreviated());
		m_patternsData.emplace("%a", datetime::get_weekday());
		m_patternsData.emplace("%B", datetime::get_month_name_abbreviated());
		m_patternsData.emplace("%b", datetime::get_month_name());
		m_patternsData.emplace("%C", datetime::get_year_short());
		m_patternsData.emplace("%c", datetime::get_year());
		m_patternsData.emplace("%D", datetime::get_date_short());
		m_patternsData.emplace("%d", datetime::get_date());
		m_patternsData.emplace("%H", datetime::get_hour_24());
		m_patternsData.emplace("%h", datetime::get_hour_12());
		m_patternsData.emplace("%i", datetime::get_minute());
		m_patternsData.emplace("%L", std::string(1, toupper(m_logLevel[0])));
		m_patternsData.emplace("%l", m_logLevel);
		m_patternsData.emplace("%M", datetime::get_day());
		m_patternsData.emplace("%m", datetime::get_month());
		m_patternsData.emplace("%n", m_loggerName);
		m_patternsData.emplace("%s", datetime::get_second());
		m_patternsData.emplace("%v", message);
		m_patternsData.emplace("%x", datetime::get_time());

		std::vector<std::string> pattern_string_tokens_vec;

		std::regex rg("(\\%[AaBbCcDdHhiLlMmnsvx]{1})");

		detail::populate_vec_with_regex_matches_from_str(pattern_string_tokens_vec, rg, pattern);

		for (int i = 0; i < pattern_string_tokens_vec.size(); ++i)
		{
			for (auto it = m_patternsData.begin(); it != m_patternsData.end(); ++it)
			{
				if (pattern_string_tokens_vec[i] == it->first)
				{
					detail::replace_in_string(pattern, pattern_string_tokens_vec[i], it->second);
				}
			}
		}

		return pattern;
		m_patternsData.clear();
	}
}
