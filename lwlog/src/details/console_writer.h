#pragma once

namespace lwlog::details
{
	class console_writer
	{
	public:
		explicit console_writer(std::FILE* stream);
		void write(std::string_view message) const;

	private:
		std::FILE* m_stream;
	};

	inline console_writer::console_writer(std::FILE* stream)
		: m_stream{ stream }
	{
		std::setvbuf(m_stream, nullptr, _IOFBF, 4194304);
	}

	inline void console_writer::write(std::string_view message) const
	{
		std::fwrite(message.data(), message.size(), 1, m_stream);
		std::fwrite("\n", 1, 1, m_stream);
	}
}
