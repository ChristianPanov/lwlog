#include "file_sink.h"
#include <iostream>
namespace lwlog::sinks
{
	file_sink::file_sink()
	{
		m_file_size_limit = 0;
		disable_color();
	}

	file_sink::~file_sink()
	{
		m_file.close();
	}

	void file_sink::init_log_file(std::string_view file_name, std::string_view path_str, std::size_t file_size_limit)
	{
		m_file_size_limit = file_size_limit;
		m_file.open(file_name, path_str);
		m_file.close();
	}

	void file_sink::sink_it(std::string_view message)
	{
		if (m_file.file_size() <= m_file_size_limit)
		{
			m_file.reopen();
			m_file.write(message.data() + std::string("\n"));
			m_file.close();
		}
	}
}
