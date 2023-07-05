#include "alignment_formatter.hpp"

namespace lwlog::details
{
	alignment_specification::alignment_specification(std::string str)
	{
		const bool has_fill_char{ !std::isdigit(str[2]) };
		const std::uint8_t flag_length = has_fill_char ? 3 : 2;

		alignment_flag = str.substr(0, flag_length);
		if (has_fill_char) fill_char = alignment_flag[2];

		switch (alignment_flag[1])
		{
		case '<': side = align_side::left;		break;
		case '>': side = align_side::right;		break;
		case '^': side = align_side::center;	break;
		}

		std::string width_str;
		for (const auto& c : str.substr(flag_length, 2))
		{
			if (std::isdigit(c)) width_str += c;
		}
		width = static_cast<std::uint8_t>(std::stoi(width_str));
		alignment_flag += width_str;

		for (const auto& c : str)
		{
			if (c == '%')
			{
				flag_to_align = { c, *(&c + 1) };
			}
			else if (c == '{')
			{
				const std::size_t found{ str.find(c) };
				flag_to_align = str.substr(found, str.find('}') - found + 1);
			}
		}
	}

	void alignment_formatter::format(std::string& pattern, const alignment_specification& spec)
	{
		const std::size_t flag_pos{ pattern.find(spec.alignment_flag) };
		const std::string to_align_formatted{ pattern.substr(flag_pos + spec.alignment_flag.size(),
			pattern.find(alignment_specification::end_flag) - flag_pos - spec.alignment_flag.size()) };

		pattern.replace(pattern.find(spec.alignment_flag), spec.alignment_flag.size(), "");
		pattern.replace(pattern.find(alignment_specification::end_flag), 2, "");
		pattern.replace(pattern.find(to_align_formatted), to_align_formatted.size(),
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