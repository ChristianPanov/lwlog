#pragma once

#include <string>
#include <cstdio>

namespace lwlog::details
{
	using stream_t = std::FILE*;

	class stream
	{
		static constexpr std::size_t internal_size = 32768;
	public:
		explicit stream(stream_t stream, std::size_t size = internal_size);
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
		std::fwrite((std::string(message) + "\n").data(), message.size() + 1, 1, m_stream);
	}
}
