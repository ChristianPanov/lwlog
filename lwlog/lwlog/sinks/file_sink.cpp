#include "file_sink.h"

#include "../formatter.h"

namespace lwlog::sinks
{
	file_sink::file_sink()
		: m_pattern("[%d, %x] [%l] [%n]: %v")
		, m_level(level::all)
	{
		set_level_visibility(m_level);
	}

	void file_sink::init_log_file(std::string_view file_name, std::string_view path_str, std::size_t file_size_limit)
	{
		m_file_size_limit = file_size_limit;
		m_file.open(file_name, path_str, file_size_limit);
	}

	void file_sink::log(std::string_view message, level log_level)
	{
		if (static_cast<std::underlying_type_t<level>>(m_level)
			& static_cast<std::underlying_type_t<level>>(log_level))
		{
			m_file.write(formatter::format(m_pattern));
			m_file.close();
		}
	}

	void file_sink::set_level_visibility(level log_level)
	{
		if (log_level == level::all) {
			m_level = level::info | level::warning
				| level::error | level::critical | level::debug;
		}
		else if (log_level == level::none) {
			m_level = level::none;
		}
		else {
			m_level = log_level;
		}
	}

	void file_sink::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}
}
