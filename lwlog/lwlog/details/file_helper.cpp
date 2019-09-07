#include "file_helper.h"

namespace details
{
	file_helper::~file_helper()
	{
		close();
	}

	void file_helper::open(const char* file_name, std::string_view path_str, append open_mode)
	{
		m_path = path_str;

		if (!std::filesystem::exists(m_path))
		{
			std::filesystem::create_directory(m_path);
		}

		m_path.append(file_name);
		m_file = std::fopen(m_path.string().data(), 
			open_mode == append::off ? "w" : "a");
	}

	void file_helper::write(std::string message)
	{
		std::size_t message_size = message.size();
		auto data = message.data();

		if (m_file != nullptr)
		{
			std::fwrite(data, 1, message_size, m_file);
		}
	}

	void file_helper::flush()
	{
		std::fflush(m_file);
	}

	void file_helper::close()
	{
		if (m_file != nullptr)
		{
			std::fclose(m_file);
			m_file = nullptr;
		}
	}

	inline std::FILE* file_helper::get_file_handler()
	{
		return m_file;
	}

	inline std::filesystem::path file_helper::get_filesys_path()
	{
		return m_path;
	}
}