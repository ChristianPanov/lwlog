#include "file_helper.h"

namespace details
{
	file_helper::~file_helper()
	{
		close();
	}

	void file_helper::open(std::string_view name, std::string_view path_str, std::size_t size_limit, truncate open_mode)
	{
		m_name = name;
		m_path = path_str;
		m_size_limit = size_limit;
		m_open_mode = open_mode;
		
		if (!std::filesystem::exists(m_path))
		{
			std::filesystem::create_directory(m_path);
		}
		else if (m_path.empty())
		{
			std::filesystem::create_directory(std::filesystem::current_path());
		}

		m_path.append(m_name);

		m_file.open(m_path, m_open_mode == truncate::on 
			? std::ios::in | std::ios::out | std::ios::trunc 
			: std::ios::in | std::ios::out | std::ios::app);
	}

	void file_helper::reopen()
	{
		if (!m_name.empty())
		{
			m_file.open(m_path, m_open_mode == truncate::on
				? std::ios::in | std::ios::out | std::ios::trunc
				: std::ios::in | std::ios::out | std::ios::app);
		}
	}

	void file_helper::write(std::string_view message)
	{
		m_file << message;
	}

	void file_helper::close()
	{
		m_file.close();
	}
}