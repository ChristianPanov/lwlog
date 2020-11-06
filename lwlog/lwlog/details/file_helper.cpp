#include "file_helper.h"

namespace lwlog::details
{
	file::file(std::string_view path, append mode)
		: m_path{ path }
		, m_mode{ mode }
	{}

	file::~file()
	{
		close();
	}

	void file::open()
	{
		if (!std::filesystem::exists(m_path.parent_path()))
		{
			std::filesystem::create_directory(m_path.parent_path());
		}

		m_file = std::fopen(m_path.string().data(), m_mode == append::on ? "a" : "w");
	}

	void file::reopen()
	{
		if (std::filesystem::exists(m_path))
		{
			m_file = std::fopen(m_path.string().data(), m_mode == append::on ? "a" : "w");
		}
	}

	void file::write(std::string_view message)
	{
		if (m_file != nullptr)
		{
			std::fwrite((std::string(message) + "\n").data(), message.size() + 1, 1, m_file);
		}
	}

	void file::close()
	{
		if (m_file != nullptr)
		{
			std::fclose(m_file);
			m_file = nullptr;
		}
	}

	bool file::exists() const
	{
		return std::filesystem::exists(m_path);
	}

	std::size_t file::size() const
	{
		return std::filesystem::file_size(m_path);
	}
}