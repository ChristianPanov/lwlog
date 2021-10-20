#pragma once

namespace lwlog::details
{
	class stream_writer
	{
	private:
		using stream_t = std::FILE*;
		static constexpr std::uint32_t s_buffer_size{ 4194304 };

	public:
		explicit stream_writer(stream_t stream);
		virtual ~stream_writer() = default;
		void write(std::string_view message);

	private:
		stream_t m_stream;
	};

	inline stream_writer::stream_writer(stream_t stream)
		: m_stream{ stream }
	{
		std::setvbuf(m_stream, NULL, _IOFBF, s_buffer_size);
	}

	inline void stream_writer::write(std::string_view message)
	{
		std::fwrite(message.data(), message.size(), 1, m_stream);
		std::fwrite("\n", 1, 1, m_stream);
	}
}
