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
		else if (m_path.parent_path().empty())
		{
			std::filesystem::create_directory(std::filesystem::current_path());
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

	void file_helper::rename(std::string_view new_name)
	{
		if (std::filesystem::exists(m_path))
		{
			m_path.replace_filename(new_name.data() + m_path.extension().string());
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

	std::filesystem::path file_helper::path() const
	{
		return m_path;
	}

	std::filesystem::path file_helper::parent_path() const
	{
		return m_path.parent_path();
	}

	std::filesystem::path file_helper::name() const
	{
		return m_path.filename().string().erase(m_path.filename().string().find(m_path.extension().string(), m_path.extension().string().length()));
	}

	std::filesystem::path file_helper::extension() const
	{
		return m_path.extension().string();
	}

	std::size_t file_helper::size() const
	{
		return std::filesystem::file_size(m_path);
	}
}