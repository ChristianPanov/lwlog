#include "rotating_file_sink.h"

namespace lwlog::sinks
{
	rotating_file_sink::rotating_file_sink()
	{
		disable_color();
		m_file_size_limit = 0;
		m_index = 0;
	}

	rotating_file_sink::~rotating_file_sink()
	{
		m_file.close();
	}

	void rotating_file_sink::sink_it(std::string_view message)
	{
		if (m_file.exists())
		{
			if (m_file.size() <= m_file_size_limit)
			{
				m_file.reopen();
				m_file.write(message.data() + std::string("\n"));
				m_file.close();
			}
			else 
			{
				rotate();
			}
		}
	}

	void rotating_file_sink::init_log_file(std::string_view path_str, int file_size_limit, int rotations)
	{
		m_file_size_limit = file_size_limit;
		m_rotations = rotations;
		m_index++;
		m_file.open(path_str);
		m_file.close();
		m_base_name = m_file.name().string();
	}

	void rotating_file_sink::rotate()
	{
		if (m_rotations > 0)
		{
			m_rotations--;
			m_file.rename(m_base_name + std::to_string(m_index++));
			m_file.open(m_file.path().string());
			m_file.close();
		}
	}
}