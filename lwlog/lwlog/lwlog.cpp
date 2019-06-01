#include "lwlog.h"

namespace lwlog
{
	logger::logger(const std::string& logger_name)
		: m_loggerName(logger_name), m_pattern("[%d, %x] [%l] [%n]: %v")
	{
		if (registry::instance().is_registry_automatic() == true)
		{
			registry::instance().register_logger(this);
		}
	}

	logger::~logger()
	{
	}

	void logger::set_name(const std::string& logger_name)
	{
		m_loggerName = logger_name;
	}

	void logger::set_logLevel_visibility(log_level logLevel)
	{
		if (logLevel == log_level::all)
		{
			m_logLevel_visibility = log_level::info | log_level::warning | log_level::error
				| log_level::critical | log_level::debug;
		}
		else if (logLevel == log_level::none)
		{
			m_logLevel_visibility = log_level::none;
		}
		else
		{
			m_logLevel_visibility = logLevel;
		}
	}

	void logger::set_pattern(const std::string& pattern)
	{
		m_pattern = pattern;
	}

	void logger::info(const std::string& message)
	{
		m_message = message;
		m_logLevel = "info";

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevel_visibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::info))
		{
			print_formatted(message, m_pattern);
		}
	}

	void logger::warning(const std::string& message)
	{
		m_message = message;
		m_logLevel = "warning";

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevel_visibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::warning))
		{
			print_formatted(message, m_pattern);
		}
	}

	void logger::error(const std::string& message)
	{
		m_message = message;
		m_logLevel = "error";

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevel_visibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::error))
		{
			print_formatted(message, m_pattern);
		}
	}

	void logger::critical(const std::string& message)
	{
		m_message = message;
		m_logLevel = "critical";

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevel_visibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::critical))
		{
			print_formatted(message, m_pattern);
		}
	}

	void logger::debug(const std::string& message)
	{
		m_message = message;
		m_logLevel = "debug";

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevel_visibility)
			& static_cast<std::underlying_type_t<log_level>>(log_level::debug))
		{
			print_formatted(message, m_pattern);
		}
	}

	void logger::print_formatted(const std::string& message, std::string pattern)
	{
		m_patterns_data.emplace("%d", datetime::get_current_date());
		m_patterns_data.emplace("%L", std::string(1, toupper(m_logLevel[0])));
		m_patterns_data.emplace("%l", m_logLevel);
		m_patterns_data.emplace("%n", m_loggerName);
		m_patterns_data.emplace("%v", message);
		m_patterns_data.emplace("%x", datetime::get_current_time());

		std::vector<std::string> pattern_string_tokens_vec;

		std::regex rg("(\\%[DdLlnvx]{1})");

		detail::populate_vec_with_regex_matches_from_str(pattern_string_tokens_vec, rg, pattern);

		for (int i = 0; i < pattern_string_tokens_vec.size(); ++i)
		{
			for (auto it = m_patterns_data.begin(); it != m_patterns_data.end(); ++it)
			{
				if (pattern_string_tokens_vec[i] == it->first)
				{
					detail::replace_in_string(pattern, pattern_string_tokens_vec[i], it->second);
				}
			}
		}

		print("{0} \n", pattern);
		m_patterns_data.clear();
	}
}