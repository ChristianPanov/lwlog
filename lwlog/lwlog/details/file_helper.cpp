#include "file_helper.h"

namespace details
{
	file_helper::file_helper()
		: m_path(std::filesystem::current_path())
		, m_size_limit(10240)
	{}

	file_helper::~file_helper()
	{
		close();
	}

	void file_helper::open(std::string_view name, std::string_view path_str, std::size_t size_limit, append open_mode)
	{
		m_path = path_str;
		m_name = name;
		m_size_limit = size_limit;

		if (!std::filesystem::exists(m_path))
		{
			std::filesystem::create_directory(m_path);
		}

		m_path.append(name);
		m_file = std::fopen(m_path.string().data(), 
			open_mode == append::off ? "w" : "a");
	}

	void file_helper::write(std::string_view message)
	{
		std::size_t message_size = message.size();
		auto data = message.data();

		if (m_file != nullptr && std::filesystem::file_size(m_path) <= m_size_limit)
		{
			std::fwrite(data, 1, message_size, m_file);
		}
	}

	void file_helper::clear()
	{
		m_path.clear();
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
			m_name.clear();
			m_size_limit = 0;
		}
	}
}