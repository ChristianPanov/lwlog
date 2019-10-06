#include "file_sink.h"

#include "../formatter.h"

namespace lwlog::sinks
{
	void file_sink::init_log_file(std::string_view file_name, std::string_view path_str, std::size_t file_size_limit)
	{
		m_file_size_limit = file_size_limit;
		m_file.open(file_name, path_str, file_size_limit);
	}

	void file_sink::sink_it(std::string_view message, level log_level)
	{
		if (static_cast<std::underlying_type_t<level>>(m_level)
			& static_cast<std::underlying_type_t<level>>(log_level))
		{
			m_file.write(message.data() + std::string("\n"));
		}

		m_file.close();
	}
}
