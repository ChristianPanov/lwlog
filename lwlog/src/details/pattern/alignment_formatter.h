#pragma once

#include <string>

namespace lwlog::details
{
	struct alignment_specification
	{
		static constexpr auto end_flag{ ":|" };

		enum class align_side { left, center, right };
		explicit alignment_specification(std::string str);

		char fill_char{ ' ' };
		align_side side{ align_side::left };
		std::uint8_t width{};

		std::string flag_to_align;
		std::string alignment_flag;
	};

	struct alignment_formatter
	{
		static void format(std::string& pattern, const alignment_specification& spec);
		static std::string align(const std::string& to_align, std::uint8_t width,
			char fill_char, alignment_specification::align_side side);

		static std::string align_left(const std::string& to_align, std::uint8_t width, char fill_char);
		static std::string align_right(const std::string& to_align, std::uint8_t width, char fill_char);
		static std::string align_center(const std::string& to_align, std::uint8_t width, char fill_char);
	};
}