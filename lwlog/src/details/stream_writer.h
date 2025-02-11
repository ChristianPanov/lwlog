#pragma once

#include <filesystem>

namespace lwlog::details
{
	template<typename FlushPolicy>
	class stream_writer
	{
	public:
		explicit stream_writer(std::FILE* stream);
		explicit stream_writer(std::string_view path);
		virtual ~stream_writer();

	public:
		void write(std::string_view message) const;
		std::FILE* handle() const;
		std::filesystem::path& filesystem_path();

	private:
		std::FILE* m_stream{ nullptr };
		std::filesystem::path m_path{};
	};
}

#include "stream_writer_impl.h"
