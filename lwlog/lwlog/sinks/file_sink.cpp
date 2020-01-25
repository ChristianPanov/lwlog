#include "file_sink.h"
#include "../formatter.h"

#include "../print.h"

namespace lwlog::sinks
{
	file_sink::~file_sink()
	{
		m_file.close();
	}

	void file_sink::init_log_file(std::string_view file_name, std::string_view path_str, std::size_t file_size_limit)
	{
		m_file_size_limit = file_size_limit;
		m_file.open(file_name.data(), path_str.data(), file_size_limit);
	}

	void file_sink::sink_it(std::string_view message)
	{
		m_file.write(message.data() + std::string("\n"));
		lwlog::print("[FILE] {0} \n", message.data());
	}
}
