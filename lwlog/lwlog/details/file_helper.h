#pragma once

#include <fstream>
#include <filesystem>

namespace lwlog::details
{
	class file_t
	{
	public:
		enum class append { off = 0, on = 1 };

	public:
		file_t() = default;
		file_t(std::string_view path, append mode = append::on);
		~file_t();

	public:
		void open();
		void reopen();
		void write(std::string_view message);
		void close();
		bool exists() const;
		std::size_t size() const;

	private:
		std::FILE* m_file{ nullptr };
		std::filesystem::path m_path;
		append m_mode{ append::on };
	};
}