#pragma once

#include <fstream>
#include <filesystem>

#include "../core.h"

namespace details
{
	class LWLOG_API file_helper
	{
	public:
		enum class truncate { off = 0, on = 1 };

	public:
		~file_helper();

		void open(std::string_view name, std::string_view path_str, std::size_t size_limit, truncate open_mode = truncate::off);
		void reopen();
		void write(std::string_view message);
		void close();

	private:
		std::ofstream m_file;
		std::string m_name;
		std::filesystem::path m_path;
		std::size_t m_size_limit;
		truncate m_open_mode;
	};
}