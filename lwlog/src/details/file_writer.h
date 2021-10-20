#pragma once

#include <fstream>
#include <filesystem>

namespace lwlog::details
{
	class file_writer
	{
	private:
		using stream_t = std::FILE*;
		static constexpr std::uint32_t s_buffer_size{ 8388608 };

	public:
		file_writer() = default;
		file_writer(std::string_view path);
		virtual ~file_writer();

	public:
		void write(std::string_view message);
		void close();
		bool exists() const;
		std::size_t size() const;
		stream_t handle() const;

	private:
		std::filesystem::path m_path;
		stream_t m_file{ nullptr };
	};
}