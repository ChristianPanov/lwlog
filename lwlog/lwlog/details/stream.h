#pragma once

#include <string_view>
#include <cstdio>

namespace lwlog::details
{
	class stream
	{
	private:
		using stream_t = std::FILE*;
		static constexpr std::uint32_t internal_size{ 4194304 };

	public:
		explicit stream(stream_t stream, std::size_t size = 4194304);
		virtual ~stream() = default;
		void write(std::string_view message);

	private:
		stream_t m_stream;
	};

	inline stream::stream(stream_t stream, std::size_t size)
		: m_stream(stream)
	{
		std::setvbuf(m_stream, NULL, _IOFBF, size);
	}

	inline void stream::write(std::string_view message)
	{
		std::fwrite(message.data(), message.size(), 1, m_stream);
		std::fwrite("\n", 1, 1, m_stream);
	}
}
