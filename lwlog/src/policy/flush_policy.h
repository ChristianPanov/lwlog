#pragma once

namespace lwlog
{
	template<std::size_t BufferSize = (1 << 22)>
	struct buffered_flush_policy
	{
		static constexpr auto buffer_size{ BufferSize };
		static void flush(std::FILE*) {}
	};

	struct immediate_flush_policy
	{
		static constexpr auto buffer_size{ (1 << 22) };
		static void flush(std::FILE* stream) { std::fflush(stream); }
	};
}
