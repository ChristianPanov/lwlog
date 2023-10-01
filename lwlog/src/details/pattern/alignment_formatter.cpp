#include "alignment_formatter.h"

namespace lwlog::details
{
	void alignment_formatter::format(std::string& pattern, const alignment_specification& spec)
	{
		const std::size_t flag_pos{ pattern.find(spec.alignment_flag) };
		const std::string to_align_formatted{ pattern.substr(flag_pos + spec.alignment_flag.size(),
			pattern.find(alignment_specification::flag_end_indicator) - flag_pos - spec.alignment_flag.size()) };

		pattern.replace(flag_pos, spec.alignment_flag.size(), "");
		pattern.replace(pattern.find(alignment_specification::flag_end_indicator, flag_pos), 2, "");
		pattern.replace(pattern.find(to_align_formatted, flag_pos), to_align_formatted.size(),
			alignment_formatter::align(to_align_formatted, spec.width, spec.fill_char, spec.side));
	}

	std::string alignment_formatter::align(const std::string& to_align, std::uint8_t width, char fill_char, 
		alignment_specification::align_side side)
	{
		switch (side)
		{
		case alignment_specification::align_side::left:		return align_left(to_align, width, fill_char);
		case alignment_specification::align_side::right:	return align_right(to_align, width, fill_char);
		case alignment_specification::align_side::center:	return align_center(to_align, width, fill_char);
		}
	}

	std::string alignment_formatter::align_left(const std::string& to_align, std::uint8_t width, char fill_char)
	{
		if (width <= to_align.size()) return to_align;
		return to_align + std::string(width - to_align.size(), fill_char);
	}

	std::string alignment_formatter::align_right(const std::string& to_align, std::uint8_t width, char fill_char)
	{
		if (width <= to_align.size()) return to_align;
		return std::string(width - to_align.size(), fill_char) + to_align;
	}

	std::string alignment_formatter::align_center(const std::string& to_align, std::uint8_t width, char fill_char)
	{
		if (width <= to_align.size()) return to_align;

		const auto alignment_width{ width - to_align.size() };
		const auto left_width{ alignment_width / 2 };
		const auto right_width{ alignment_width % 2 ? left_width + 1 : left_width };

		return std::string(left_width, fill_char) + to_align + std::string(right_width, fill_char);
	}
}