#pragma once

#include <fstream>
#include <filesystem>

#include "core.h"

namespace lwlog::details
{
	class LWLOG_API file_helper
	{
	public:
		enum class truncate { off = 0, on = 1 };

	public:
		~file_helper();

		void open(std::string_view path_str, truncate open_mode = truncate::off);
		void reopen();
		void write(std::string_view message);
		void clear();
		bool exists();
		void close();
		std::size_t size() const;

	private:
		std::FILE* m_file{ nullptr };
		std::filesystem::path m_path;
		truncate m_open_mode{ truncate::off };
	};
}