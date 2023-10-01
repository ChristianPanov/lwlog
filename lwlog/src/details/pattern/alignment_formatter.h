#pragma once

#include <string>

namespace lwlog::details
{
	struct alignment_specification
	{
		static constexpr auto flag_end_indicator{ ":|" };

		enum class align_side : std::uint8_t
		{
			left,
			center,
			right
		};

		char fill_char{};
		align_side side{};
		std::uint8_t width{};
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