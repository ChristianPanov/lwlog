#pragma once

#include <fstream>
#include <filesystem>

#include "../core.h"

namespace details
{
	class LWLOG_API file_helper
	{
	public:
		enum class append { off = 0, on = 1 };

	public:
		explicit file_helper() = default;
		virtual ~file_helper();

		void open(const char* file_name, std::string_view path, append open_mode = append::on);
		void write(std::string message);
		void flush();
		void close();

		inline std::FILE* get_file_handler();
		inline std::filesystem::path get_filesys_path();

	private:
		std::FILE* m_file{nullptr};
		std::filesystem::path m_path;
	};
}