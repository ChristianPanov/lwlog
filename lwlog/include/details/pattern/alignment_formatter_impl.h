#pragma once

namespace lwlog::details
{
	alignment_info::alignment_info(char fill_char, align_side side, std::uint8_t width, std::string_view flag)
		: fill_char{ fill_char }
		, side{ side }
		, width{ width }
		, flag{ flag }
	{}

	template<typename BufferLimits>
	void alignment_formatter<BufferLimits>::format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, 
		char* padding_buffer, const alignment_info& alignment_flag_info)
	{
		constexpr std::size_t flag_end_indicator_size{ 2 };

		const std::size_t flag_size{ alignment_flag_info.flag.size() };
		const std::size_t flag_pos{ pattern_buffer.data().find(alignment_flag_info.flag) };
		const std::size_t flag_end_pos{ pattern_buffer.data().find(alignment_info::flag_end, flag_pos + flag_size) };
		const std::size_t to_align_size{ flag_end_pos - flag_pos - flag_size };

		alignment_formatter::apply_padding(pattern_buffer, padding_buffer,
			flag_end_pos - to_align_size, to_align_size,
			alignment_flag_info.width,
			alignment_flag_info.fill_char,
			alignment_flag_info.side
		);

		pattern_buffer.erase(flag_pos + flag_size + alignment_flag_info.width, flag_end_indicator_size);
		pattern_buffer.erase(flag_pos, flag_size);
	}

	template<typename BufferLimits>
	void alignment_formatter<BufferLimits>::apply_padding(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, 
		char* padding_buffer, std::size_t to_align_pos, std::size_t to_align_size, std::uint8_t width, char fill_char, alignment_info::align_side side)
	{
		switch (side)
		{
		case alignment_info::align_side::left:
			pad_left(pattern_buffer, padding_buffer, to_align_pos, to_align_size, width, fill_char);
			break;
		case alignment_info::align_side::right:
			pad_right(pattern_buffer, padding_buffer, to_align_pos, to_align_size, width, fill_char);
			break;
		case alignment_info::align_side::center:
			pad_center(pattern_buffer, padding_buffer, to_align_pos, to_align_size, width, fill_char);
			break;
		}
	}

	template<typename BufferLimits>
	void alignment_formatter<BufferLimits>::pad_left(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, 
		char* padding_buffer, std::size_t to_align_pos, std::size_t to_align_size, std::uint8_t width, char fill_char)
	{
		const std::size_t padding_width{ width - to_align_size };

		std::memset(padding_buffer, fill_char, padding_width);

		pattern_buffer.insert(to_align_pos, padding_width, padding_buffer);
	}

	template<typename BufferLimits>
	void alignment_formatter<BufferLimits>::pad_right(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, 
		char* padding_buffer, std::size_t to_align_pos, std::size_t to_align_size, std::uint8_t width, char fill_char)
	{
		const std::size_t padding_width{ width - to_align_size };

		std::memset(padding_buffer, fill_char, padding_width);

		pattern_buffer.insert(to_align_pos + to_align_size, padding_width, padding_buffer);
	}

	template<typename BufferLimits>
	void alignment_formatter<BufferLimits>::pad_center(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, 
		char* padding_buffer, std::size_t to_align_pos, std::size_t to_align_size, std::uint8_t width, char fill_char)
	{
		const std::size_t total_padding{ width - to_align_size };
		const std::size_t left_padding{ total_padding / 2 };
		const std::size_t right_padding{ total_padding - left_padding };

		std::memset(padding_buffer, fill_char, right_padding);

		pattern_buffer.insert(to_align_pos, left_padding, padding_buffer);
		pattern_buffer.insert(to_align_pos + to_align_size + left_padding, right_padding, padding_buffer);
	}
}