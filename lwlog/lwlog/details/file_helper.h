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
		file_helper();
		virtual ~file_helper();

		void open(std::string_view name, std::string_view path_str = "", std::size_t size_limit = 10240, append open_mode = append::on);
		void write(std::string_view message);
		void clear();
		void flush();
		void close();

	private:
		std::FILE* m_file{ nullptr };
		std::filesystem::path m_path;
		std::string m_name;
		std::size_t m_size_limit;
	};
}