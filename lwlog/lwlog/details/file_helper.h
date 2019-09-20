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

		void open(std::string_view file_name, std::string_view path, append open_mode = append::on);
		void write(std::string_view message);
		void clear();
		void flush();
		void close();

		inline std::size_t get_size() const;
		inline std::string get_filename() const;
		inline std::FILE* get_file_ptr_handler() const;
		inline std::filesystem::path get_filesys_path() const;

	private:
		std::FILE* m_file{nullptr};
		std::filesystem::path m_path;
		std::string m_filename;
	};
}