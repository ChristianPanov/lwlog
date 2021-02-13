#pragma once

#include <fstream>
#include <filesystem>

namespace lwlog::details
{
	class file_writer
	{
	private:
		static constexpr std::uint32_t internal_size{ 4194304 };

	public:
		file_writer() = default;
		file_writer(std::string_view path, std::size_t buffer_size = internal_size);
		virtual ~file_writer();

	public:
		void write(std::string_view message);
		void close();
		bool exists() const;
		std::size_t size() const;
		std::FILE* handle() const;

	private:
		std::filesystem::path m_path;
		std::FILE* m_file{ nullptr };
	};
}