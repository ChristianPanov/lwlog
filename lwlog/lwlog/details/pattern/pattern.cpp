#include "pattern.h"
#include "level.h"
#include "format_data.h"
#include "color_format_data.h"

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
		std::string temp = m_pattern;
		std::vector<std::string> buff;
		while (strstr(temp.data(), "{") && strstr(temp.data(), "}"))
		{
			std::size_t first_pos = temp.find("{");
			std::size_t last_pos = temp.find("}", first_pos + 1);
			std::size_t flag_length = last_pos - first_pos + 1;
			buff.push_back(temp.substr(first_pos, flag_length));
			temp.replace(first_pos, flag_length, "");
		}
		return buff;
	}

	std::vector<std::string> pattern::short_flags()
	{
		std::string temp = m_pattern;
		std::vector<std::string> buff;
		while (strstr(temp.data(), "%"))
		{
			std::size_t found = temp.find("%", 0);
			std::size_t flag_length = 2;
			buff.push_back(temp.substr(found, 2));
			temp.replace(found, 2, "");
		}
		return buff;
	}
}