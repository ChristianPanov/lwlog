#include "file_helper.h"

namespace lwlog::details
{
	file_t::file_t(std::string_view path, append mode)
		: m_path{ path }
		, m_mode{ mode }
	{}

	file_t::~file_t()
	{
		close();
	}

	void file_t::open()
	{
		if (!std::filesystem::exists(m_path.parent_path()))
		{
			std::filesystem::create_directory(m_path.parent_path());
		}

		m_file = std::fopen(m_path.string().data(), m_mode == append::on ? "a" : "w");
	}

	void file_t::reopen()
	{
		if (std::filesystem::exists(m_path))
		{
			m_file = std::fopen(m_path.string().data(), m_mode == append::on ? "a" : "w");
		}
	}

	void file_t::write(std::string_view message)
	{
		if (m_file != nullptr)
		{
			std::fwrite((std::string(message) + "\n").data(), message.size() + 1, 1, m_file);
		}
	}

	void file_t::close()
	{
		if (m_file != nullptr)
		{
			std::fclose(m_file);
			m_file = nullptr;
		}
	}

	bool file_t::exists() const
	{
		return std::filesystem::exists(m_path);
	}

	std::size_t file_t::size() const
	{
		return std::filesystem::file_size(m_path);
	}
}