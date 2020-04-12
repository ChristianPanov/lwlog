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

		m_file = std::fopen(m_path.string().data(), m_open_mode == truncate::off ? "a" : "w");
	}

	void file_helper::reopen()
	{
		if (std::filesystem::exists(m_path))
		{
			m_file = std::fopen(m_path.string().data(), m_open_mode == truncate::off ? "a" : "w");
		}
	}

	void file_helper::write(std::string_view message)
	{
		if (m_file != nullptr)
		{
			std::setvbuf(m_file, NULL, _IOFBF, 32768);
			std::fwrite(message.data(), message.size(), 1, m_file);
		}
	}

	void file_helper::clear()
	{
		m_path.clear();
	}

	bool file_helper::exists()
	{
		return std::filesystem::exists(m_path);
	}

	void file_helper::close()
	{
		if (m_file != nullptr)
		{
			std::fclose(m_file);
			m_file = nullptr;
		}
	}

	std::size_t file_helper::size() const
	{
		return std::filesystem::file_size(m_path);
	}
}