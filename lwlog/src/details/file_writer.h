#pragma once

#include <filesystem>

namespace lwlog::details
{
	class file_writer
	{
	public:
		file_writer() = default;
		explicit file_writer(std::string_view path);
		virtual ~file_writer();

	public:
		void write(std::string_view message) const;
		std::FILE* handle() const;
		std::filesystem::path& filesystem_path();

	private:
		std::FILE* m_file{ nullptr };
		std::filesystem::path m_path;
	};
}