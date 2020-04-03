#include "file_helper.h"

namespace lwlog::details
{
	file_helper::~file_helper()
	{
		close();
	}

	void file_helper::open(std::string_view path_str, truncate open_mode)
	{
		m_path = path_str;
		m_open_mode = open_mode;
		
		if (!std::filesystem::exists(m_path.parent_path()))
		{
			std::filesystem::create_directory(m_path.parent_path());
		}

		m_file.open(m_path, m_open_mode == truncate::on 
			? std::ios::in | std::ios::out | std::ios::trunc 
			: std::ios::in | std::ios::out | std::ios::app);
	}

	void file_helper::reopen()
	{
		if (std::filesystem::exists(m_path))
		{
			m_file.open(m_path, m_open_mode == truncate::on
				? std::ios::in | std::ios::out | std::ios::trunc
				: std::ios::in | std::ios::out | std::ios::app);
		}
	}

	void file_helper::write(std::string_view message)
	{
		if (std::filesystem::exists(m_path))
		{
			m_file << message;
		}
	}

	void file_helper::close()
	{
		if (std::filesystem::exists(m_path))
		{
			m_file.close();
		}
	}

	bool file_helper::exists()
	{
		return std::filesystem::exists(m_path);
	}

	std::size_t file_helper::size() const
	{
		return std::filesystem::file_size(m_path);
	}
}