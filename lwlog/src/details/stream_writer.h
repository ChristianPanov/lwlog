#pragma once

namespace lwlog::details
{
	class stream_writer
	{
	public:
		explicit stream_writer(std::FILE* stream);
		void write(std::string_view message);

	private:
		std::FILE* m_stream;
	};

	inline stream_writer::stream_writer(std::FILE* stream)
		: m_stream{ stream }
	{
		std::setvbuf(m_stream, NULL, _IOFBF, 4194304);
	}

	inline void stream_writer::write(std::string_view message)
	{
		std::fwrite(message.data(), message.size(), 1, m_stream);
		std::fwrite("\n", 1, 1, m_stream);
	}
}
