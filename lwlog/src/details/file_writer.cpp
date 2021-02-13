#include "file_writer.h"

namespace lwlog::details
{
	file_writer::file_writer(std::string_view path, std::size_t buffer_size)
		: m_path{ path }
	{
		if (!std::filesystem::exists(m_path.parent_path()))
		{
			std::filesystem::create_directory(m_path.parent_path());
		}

		m_file = std::fopen(m_path.string().data(), "a");
		std::setvbuf(m_file, NULL, _IOFBF, buffer_size);
	}

	file_writer::~file_writer()
	{
		close();
	}

	void file_writer::write(std::string_view message)
	{
		if (m_file != nullptr)
		{
			std::fwrite((std::string(message) + "\n").data(), message.size() + 1, 1, m_file);
		}
	}

	void file_writer::close()
	{
		if (m_file != nullptr)
		{
			std::fclose(m_file);
			m_file = nullptr;
		}
	}

	bool file_writer::exists() const
	{
		return std::filesystem::exists(m_path);
	}

	std::size_t file_writer::size() const
	{
		return std::filesystem::file_size(m_path);
	}

	std::FILE* file_writer::handle() const
	{
		return m_file;
	}
}