#include "pattern_compiler.h"
#include "level.h"
#include "logger_formatters.h"
#include "datetime_formatters.h"
#include "color_format_data.h"

namespace lwlog::details
{
	pattern_compiler::pattern_compiler(const log_message& message)
		: m_message{ message }
	{}

	std::string pattern_compiler::compile()
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

	void pattern_compiler::compile_colors(std::string& pattern)
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

	void pattern_compiler::format_attribute(log_message& message, std::string_view attribute, std::string_view value)
	{
		while (strstr(message.pattern.data(), attribute.data()))
		{
			message.pattern.replace(message.pattern.find(attribute), attribute.length(), value);
		}
	}

	void pattern_compiler::format_attribute(log_message& message, std::string_view verbose,
		std::string_view shortened, std::string_view value)
	{
		while (strstr(message.pattern.data(), verbose.data()))
		{
			message.pattern.replace(message.pattern.find(verbose), verbose.length(), value);
		}

		while (strstr(message.pattern.data(), shortened.data()))
		{
			message.pattern.replace(message.pattern.find(shortened), shortened.length(), value);
		}
	}

	bool pattern_compiler::contains(std::string_view attribute)
	{
		return strstr(m_message.pattern.data(), attribute.data());
	}

	bool pattern_compiler::contains(std::string_view verbose, std::string_view shortened)
	{
		return strstr(m_message.pattern.data(), verbose.data()) ||
			strstr(m_message.pattern.data(), shortened.data());
	}

	pattern_compiler::formatter_storage pattern_compiler::handle_logger_formatters()
	{
		formatter_storage storage;
		if (contains("{name}", "%n"))
			storage.push_back(std::make_shared<logger_name_formatter>());
		if (contains("{level}", "%l"))
			storage.push_back(std::make_shared<level_formatter>());
		if (contains("^level^"))
			storage.push_back(std::make_shared<level_color_formatter>());
		if (contains("{message}", "%v"))
			storage.push_back(std::make_shared<message_formatter>());
		if (contains("{thread}", "%t"))
			storage.push_back(std::make_shared<thread_id_formatter>());
		return storage;
	}

	pattern_compiler::formatter_storage pattern_compiler::handle_datetime_formatters()
	{
		formatter_storage storage;
		if (contains("{date}", "%F"))
			storage.push_back(std::make_shared<date_formatter>());
		if (contains("{date_short}", "%D"))
			storage.push_back(std::make_shared<date_short_formatter>());
		if (contains("{year}", "%Y"))
			storage.push_back(std::make_shared<year_formatter>());
		if (contains("{year_short}", "%y"))
			storage.push_back(std::make_shared<year_short_formatter>());
		if (contains("{month}", "%m"))
			storage.push_back(std::make_shared<month_formatter>());
		if (contains("{month_name}", "%B"))
			storage.push_back(std::make_shared<month_name_formatter>());
		if (contains("{month_name_short}", "%b"))
			storage.push_back(std::make_shared<month_name_short_formatter>());
		if (contains("{day}", "%d"))
			storage.push_back(std::make_shared<day_formatter>());
		if (contains("{weekday}", "%A"))
			storage.push_back(std::make_shared<weekday_name_formatter>());
		if (contains("{weekday_short}", "%a"))
			storage.push_back(std::make_shared<weekday_name_short_formatter>());
		if (contains("{time}", "%T"))
			storage.push_back(std::make_shared<time_formatter>());
		if (contains("{24_clock}", "%R"))
			storage.push_back(std::make_shared<hour_clock_24_formatter>());
		if (contains("{12_clock}", "%r"))
			storage.push_back(std::make_shared<hour_clock_12_formatter>());
		if (contains("{ampm}", "%p"))
			storage.push_back(std::make_shared<ampm_formatter>());
		if (contains("{hour_24}", "%H"))
			storage.push_back(std::make_shared<hour_24_formatter>());
		if (contains("{hour_12}", "%I"))
			storage.push_back(std::make_shared<hour_12_formatter>());
		if (contains("{minute}", "%M"))
			storage.push_back(std::make_shared<minute_formatter>());
		if (contains("{second}", "%S"))
			storage.push_back(std::make_shared<second_formatter>());
		return storage;
	}
}