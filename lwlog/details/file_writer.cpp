#include "file_writer.h"

namespace lwlog::details
{
	file_writer::file_writer(std::string_view path)
		: m_path{ path }
	{
		if (!std::filesystem::exists(m_path.parent_path()))
		{
			std::filesystem::create_directory(m_path.parent_path());
		}

		m_file = std::fopen(m_path.string().data(), "a");
		std::setvbuf(m_file, NULL, _IOFBF, 8388608);
	}

	file_writer::~file_writer()
	{
		if (m_file != nullptr)
		{
			std::fclose(m_file);
			m_file = nullptr;
		}
	}

	void file_writer::write(std::string_view message)
	{
		if (m_file != nullptr)
		{
			std::fwrite(message.data(), message.size(), 1, m_file);
			std::fwrite("\n", 1, 1, m_file);
		}
	}

	std::FILE* file_writer::handle() const
	{
		return m_file;
	}

	std::filesystem::path& file_writer::filesystem_path()
	{
		return m_path;
	}
}