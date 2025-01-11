#include "alignment_formatter.h"
#include <iostream>

namespace lwlog::details
{
	alignment_info::alignment_info(char fill_char, align_side side, std::uint8_t width, std::string_view flag)
		: fill_char	{ fill_char }
		, side		{ side		}
		, width		{ width		}
		, flag		{ flag		}
	{}

	void alignment_formatter::format(memory_buffer<>& buffer, const alignment_info& alignment_flag_info)
	{
		constexpr std::size_t flag_end_indicator_size{ 2 };

		const std::size_t flag_size		{ alignment_flag_info.flag.size() };
		const std::size_t flag_pos		{ buffer.data().find(alignment_flag_info.flag) };
		const std::size_t flag_end_pos	{ buffer.data().find(alignment_info::flag_end, flag_pos + flag_size) };
		const std::size_t to_align_size	{ flag_end_pos - flag_pos - flag_size };

		alignment_formatter::apply_padding(buffer, 
			flag_end_pos - to_align_size, to_align_size, 
			alignment_flag_info.width,
			alignment_flag_info.fill_char, 
			alignment_flag_info.side
		);

		buffer.erase(flag_pos + flag_size + alignment_flag_info.width, flag_end_indicator_size);
		buffer.erase(flag_pos, flag_size);
	}

	void alignment_formatter::apply_padding(memory_buffer<>& buffer, std::size_t to_align_pos, std::size_t to_align_size,
		std::uint8_t width, char fill_char, alignment_info::align_side side)
	{
		switch (side)
		{
		case alignment_info::align_side::left:		
			pad_left(buffer, to_align_pos, to_align_size, width, fill_char);
			break;
		case alignment_info::align_side::right:		
			pad_right(buffer, to_align_pos, to_align_size, width, fill_char);
			break;
		case alignment_info::align_side::center:	
			pad_center(buffer, to_align_pos, to_align_size, width, fill_char);
			break;
		}
	}

	void alignment_formatter::pad_left(memory_buffer<>& buffer, std::size_t to_align_pos,
		std::size_t to_align_size, std::uint8_t width, char fill_char)
	{
		const std::size_t padding_width{ width - to_align_size };

		char padding[12]{};
		std::memset(padding, fill_char, padding_width);

        buffer.insert(to_align_pos, padding_width, padding);
	}

	void alignment_formatter::pad_right(memory_buffer<>& buffer, std::size_t to_align_pos,
		std::size_t to_align_size, std::uint8_t width, char fill_char)
	{
		const std::size_t padding_width{ width - to_align_size };

		char padding[12]{};
		std::memset(padding, fill_char, padding_width);

		buffer.insert(to_align_pos + to_align_size, padding_width, padding);
	}

	void alignment_formatter::pad_center(memory_buffer<>& buffer, std::size_t to_align_pos,
		std::size_t to_align_size, std::uint8_t width, char fill_char)
	{
		const std::size_t total_padding{ width - to_align_size };
		const std::size_t left_padding{ total_padding / 2 };
		const std::size_t right_padding{ total_padding - left_padding };

		char padding[12]{};
		std::memset(padding, fill_char, right_padding);

		buffer.insert(to_align_pos, left_padding, padding);
		buffer.insert(to_align_pos + to_align_size + left_padding, right_padding, padding);
	}
}