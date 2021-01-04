#pragma once

#include <fstream>
#include <filesystem>

namespace lwlog::details
{
	class file_writer
	{
	public:
		enum class append { off = 0, on = 1 };

	public:
		file_writer() = default;
		file_writer(std::string_view path, append mode = append::on);
		~file_writer();

	public:
		void open(std::string_view path, append mode = append::on);
		void reopen();
		void write(std::string_view message);
		void close();
		bool exists() const;
		std::size_t size() const;
		std::FILE* handle() const;

	private:
		append m_mode{ append::on };
		std::filesystem::path m_path;
		std::FILE* m_file{ nullptr };
	};
}