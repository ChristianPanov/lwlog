#pragma once

#include <string>
#include <cstdint>

#include "details/memory_buffer.h"

namespace lwlog::details
{
	struct alignment_info
	{
		static constexpr auto flag_end{ ":|" };

		enum class align_side : std::uint8_t
		{
			left	= '<',
			right	= '>',
			center	= '^'
		};

		alignment_info(char fill_char, align_side side, std::uint8_t width, std::string_view flag);

		char fill_char{};
		align_side side{};
		std::uint8_t width{};
		std::string flag;
	};

	template<typename BufferLimits>
	struct alignment_formatter
	{
		static void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* padding_buffer, 
			const alignment_info& alignment_flag_info);
		static void apply_padding(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* padding_buffer, 
			std::size_t to_align_pos, std::size_t to_align_size, std::uint8_t width, char fill_char, alignment_info::align_side side);

		static void pad_left(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* padding_buffer, 
			std::size_t to_align_pos, std::size_t to_align_size, std::uint8_t width, char fill_char);
		static void pad_right(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* padding_buffer, 
			std::size_t to_align_pos, std::size_t to_align_size, std::uint8_t width, char fill_char);
		static void pad_center(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* padding_buffer, 
			std::size_t to_align_pos, std::size_t to_align_size, std::uint8_t width, char fill_char);
	};
}

#include "alignment_formatter_impl.h"