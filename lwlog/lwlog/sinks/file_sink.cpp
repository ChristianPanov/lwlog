#include "file_sink.h"

namespace lwlog::sinks
{
	file_sink::file_sink()
	{
		disable_color();
	}

	file_sink::~file_sink()
	{
		m_file.close();
	}

	void file_sink::init_log_file(std::string_view file_name, std::string_view path_str, std::size_t file_size_limit)
	{
		m_file.open(file_name, path_str, file_size_limit);
		m_file.close();
	}

	void file_sink::sink_it(std::string_view message)
	{
		m_file.reopen();
		m_file.write(message.data() + std::string("\n"));
		m_file.close();
	}
}
