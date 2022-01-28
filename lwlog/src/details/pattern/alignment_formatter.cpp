#include "alignment_formatter.h"

namespace lwlog::details
{
	alignment_specification::alignment_specification(std::string str)
		: fill_char{ ' ' }
		, side{ align_side::left }
	{
		bool has_fill_char = !std::isdigit(str[2]) ? true : false;
		std::uint8_t flag_length = has_fill_char ? 3 : 2;
		flag = str.substr(0, flag_length);
		if (has_fill_char) fill_char = flag[2];

		switch (flag[1])
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
		width = std::stoi(width_str);
		flag += width_str;

		for (const auto& c : str)
		{
			if (c == '%')
			{
				to_align = { c, *(&c + 1) };
			}
			else if (c == '{')
			{
				std::size_t found = str.find(c);
				to_align = str.substr(found, str.find('}') - found + 1);
			}
		}
	}

	void alignment_formatter::format(std::string& pattern, const alignment_specification& spec)
	{
		std::size_t flag_pos = pattern.find(spec.flag);
		std::string to_align_formatted = pattern.substr(flag_pos + spec.flag.size(),
			pattern.find(alignment_flag::end) - flag_pos - spec.flag.size());

		pattern.replace(pattern.find(spec.flag), spec.flag.size(), "");
		pattern.replace(pattern.find(alignment_flag::end), 2, "");
		pattern.replace(pattern.find(to_align_formatted), to_align_formatted.size(),
			align(to_align_formatted, spec.width, spec.fill_char, spec.side));
	}

	std::string alignment_formatter::align(const std::string& to_align, std::uint8_t width, char fill_char, 
		alignment_specification::align_side side)
	{
		switch (side)
		{
		case alignment_specification::align_side::left:
			return align_left(to_align, width, fill_char);
		case alignment_specification::align_side::right:
			return align_right(to_align, width, fill_char);
		case alignment_specification::align_side::center:
			return align_center(to_align, width, fill_char);
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
		else
		{
			auto alignment_width = width - to_align.size();
			auto left_width = alignment_width / 2;
			auto right_width = alignment_width % 2 ? left_width + 1 : left_width;

			return std::string(left_width, fill_char) + to_align + std::string(right_width, fill_char);
		}
	}
}