#pragma once

#include <fstream>
#include <filesystem>

#include "../core.h"

namespace lwlog::details
{
	class LWLOG_API file_helper
	{
	public:
		enum class truncate { off = 0, on = 1 };

	public:
		~file_helper();

		void open(std::string_view name, std::string_view path_str, truncate open_mode = truncate::off);
		void reopen();
		void write(std::string_view message);
		void close();
		std::size_t file_size() const;

	private:
		std::ofstream m_file;
		std::string m_name;
		std::filesystem::path m_path;
		truncate m_open_mode{ truncate::off };
	};
}