#include "pattern.h"
#include "color_format_data.h"
#include "format_data.h"

namespace lwlog::details
{
	std::string pattern::compile(log_message& log_msg)
	{
		for (const auto& formatter : m_formatters)
		{
			formatter->format(m_pattern, log_msg);
		}

		return m_pattern;
	}

	void pattern::handle_flag_formatters()
	{
		if (strstr(m_pattern.data(), "{") && strstr(m_pattern.data(), "}"))
		{
			for (const auto& flag : this->verbose_flags())
			{
				if (verbose_logger_data[flag])
				{
					m_formatters.push_back(verbose_logger_data[flag]);
				}
			}
			for (const auto& flag : this->verbose_flags())
			{
				if (verbose_datetime_data[flag])
				{
					m_formatters.push_back(verbose_datetime_data[flag]);
				}
			}
		}
		if (strstr(m_pattern.data(), "%"))
		{
			for (const auto& flag : this->short_flags())
			{
				if (shortened_logger_data[flag])
				{
					m_formatters.push_back(shortened_logger_data[flag]);
				}
			}
			for (const auto& flag : this->short_flags())
			{
				if (shortened_datetime_data[flag])
				{
					m_formatters.push_back(shortened_datetime_data[flag]);
				}
			}
		}
	}

	void pattern::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}

	std::string& pattern::data()
	{
		return m_pattern;
	}

	void pattern::compile_colors(std::string& pattern)
	{
		if (strstr(pattern.data(), "^"))
		{
			for (const auto& [key, value] : color_data)
			{
				while (strstr(pattern.data(), key.data()))
				{
					pattern.replace(pattern.find(key), key.length(), value);
				}
			}
		}
	}

	void pattern::format_attribute(std::string& pattern, flag::flag_pair flags, std::string_view value)
	{
		const auto& [verbose, shortened] = flags;
		if (!verbose.empty())
		{
			while (strstr(pattern.data(), verbose.data()))
			{
				pattern.replace(pattern.find(verbose), verbose.length(), value);
			}
		}
		if (!shortened.empty())
		{
			while (strstr(pattern.data(), shortened.data()))
			{
				pattern.replace(pattern.find(shortened), shortened.length(), value);
			}
		}
	}

	bool pattern::contains(flag::flag_pair flags)
	{
		return strstr(m_pattern.data(), flags.verbose.data()) ||
			strstr(m_pattern.data(), flags.shortened.data());
	}

	std::vector<std::string> pattern::verbose_flags()
	{
		std::vector<std::string> buff;
		size_t pos = m_pattern.find("{", 0);
		while (pos != std::string::npos)
		{
			buff.push_back(m_pattern.substr(pos, m_pattern.find("}", pos) - pos + 1));
			pos = m_pattern.find("{", pos + 1);
		}
		return buff;
	}

	std::vector<std::string> pattern::short_flags()
	{
		std::vector<std::string> buff;
		size_t pos = m_pattern.find("%", 0);
		while (pos != std::string::npos)
		{
			buff.push_back(m_pattern.substr(pos, 2));
			pos = m_pattern.find("%", pos + 1);
		}
		return buff;
	}
}