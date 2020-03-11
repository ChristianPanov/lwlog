#include "file_sink.h"

namespace lwlog::sinks
{
	file_sink::file_sink()
	{
		disable_color();
		m_file_size_limit = 0;
	}

	file_sink::~file_sink()
	{
		m_file.close();
	}

	void file_sink::sink_it(std::string_view message) 
	{
		if (m_file.exists())
		{
			if (m_file.size() <= m_file_size_limit)
			{
				m_file.reopen();
				m_file.write(message.data() + std::string("\n"));
				m_file.close();
			}
		}
	}

	void file_sink::init_log_file(std::string_view path_str, int file_size_limit)
	{
		m_file_size_limit = file_size_limit;
		m_file.open(path_str);
		m_file.close();
	}
}
