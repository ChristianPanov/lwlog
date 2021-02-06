#include "pattern.h"
#include "level.h"
#include "logger_formatters.h"
#include "datetime_formatters.h"
#include "color_format_data.h"

namespace lwlog::details
{
	pattern::pattern(const log_message& message)
		: m_message{ message }
	{}

	std::string pattern::compile()
	{
		for (const auto& formatter : handle_logger_formatters())
		{
			formatter->format(m_message);
		}
		for (const auto& formatter : handle_datetime_formatters())
		{
			formatter->format(m_message);
		}
		return m_message.pattern;
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

	void pattern::format_attribute(log_message& message, flag::flag_pair flags, std::string_view value)
	{
		const auto& [verbose, shortened] = flags;
		if (!verbose.empty())
		{
			while (strstr(message.pattern.data(), verbose.data()))
			{
				message.pattern.replace(message.pattern.find(verbose), verbose.length(), value);
			}
		}
		if (!shortened.empty())
		{
			while (strstr(message.pattern.data(), shortened.data()))
			{
				message.pattern.replace(message.pattern.find(shortened), shortened.length(), value);
			}
		}
	}

	bool pattern::contains(flag::flag_pair flags)
	{
		return strstr(m_message.pattern.data(), flags.verbose.data()) ||
			strstr(m_message.pattern.data(), flags.shortened.data());
	}

	pattern::formatter_storage pattern::handle_logger_formatters()
	{
		formatter_storage storage;
		if (contains(flag::logger_name))
			storage.push_back(std::make_shared<logger_name_formatter>());
		if (contains(flag::level))
			storage.push_back(std::make_shared<level_formatter>());
		if (contains(flag::level_color))
			storage.push_back(std::make_shared<level_color_formatter>());
		if (contains(flag::message))
			storage.push_back(std::make_shared<message_formatter>());
		if (contains(flag::thread_id))
			storage.push_back(std::make_shared<thread_id_formatter>());
		return storage;
	}

	pattern::formatter_storage pattern::handle_datetime_formatters()
	{
		formatter_storage storage;
		if (contains(flag::date))
			storage.push_back(std::make_shared<date_formatter>());
		if (contains(flag::date_short))
			storage.push_back(std::make_shared<date_short_formatter>());
		if (contains(flag::year))
			storage.push_back(std::make_shared<year_formatter>());
		if (contains(flag::year_short))
			storage.push_back(std::make_shared<year_short_formatter>());
		if (contains(flag::month))
			storage.push_back(std::make_shared<month_formatter>());
		if (contains(flag::month_name))
			storage.push_back(std::make_shared<month_name_formatter>());
		if (contains(flag::month_name_short))
			storage.push_back(std::make_shared<month_name_short_formatter>());
		if (contains(flag::day))
			storage.push_back(std::make_shared<day_formatter>());
		if (contains(flag::weekday))
			storage.push_back(std::make_shared<weekday_name_formatter>());
		if (contains(flag::weekday_short))
			storage.push_back(std::make_shared<weekday_name_short_formatter>());
		if (contains(flag::time))
			storage.push_back(std::make_shared<time_formatter>());
		if (contains(flag::hour_clock_24))
			storage.push_back(std::make_shared<hour_clock_24_formatter>());
		if (contains(flag::hour_clock_12))
			storage.push_back(std::make_shared<hour_clock_12_formatter>());
		if (contains(flag::ampm))
			storage.push_back(std::make_shared<ampm_formatter>());
		if (contains(flag::hour_24))
			storage.push_back(std::make_shared<hour_24_formatter>());
		if (contains(flag::hour_12))
			storage.push_back(std::make_shared<hour_12_formatter>());
		if (contains(flag::minute))
			storage.push_back(std::make_shared<minute_formatter>());
		if (contains(flag::second))
			storage.push_back(std::make_shared<second_formatter>());
		return storage;
	}
}