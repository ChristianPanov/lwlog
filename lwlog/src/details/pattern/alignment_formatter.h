#pragma once

namespace lwlog::details
{
	struct alignment_specification
	{
		enum class align_side { left, center, right };
		explicit alignment_specification(std::string str)
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
					to_align = std::string(1, c) + std::string(1, *(&c + 1));
				else if (c == '{')
					to_align = str.substr(str.find(c), str.find("}") - str.find(c) + 1);
			}
		}

		char fill_char{};
		align_side side{};
		std::uint8_t width{};
		std::string to_align;
		std::string flag;
	};

	struct alignment_formatter
	{
		static void format(std::string& pattern, alignment_specification spec)
		{
			std::string to_align_formatter = pattern.substr(pattern.find(spec.flag) + spec.flag.size(),
				pattern.find("|:") - pattern.find(spec.flag) - spec.flag.size());

			pattern.replace(pattern.find(spec.flag), spec.flag.size(), "");
			pattern.replace(pattern.find("|:"), 2, "");
			pattern.replace(pattern.find(to_align_formatter), to_align_formatter.size(),
				align(to_align_formatter, spec.width, spec.fill_char, spec.side));
		}

		static std::string align(std::string to_align, std::uint8_t width,
			char fill_char, alignment_specification::align_side side)
		{
			switch (side)
			{
			case alignment_specification::align_side::left:
				return align_left(to_align, width, fill_char);
				break;
			case alignment_specification::align_side::right:
				return align_right(to_align, width, fill_char);
				break;
			case alignment_specification::align_side::center:
				return align_center(to_align, width, fill_char);
				break;
			}
		}

		static std::string align_left(std::string to_align, std::uint8_t width, char fill_char)
		{
			if (width <= to_align.size())
				return to_align;
			else
				return to_align + std::string(width - to_align.size(), fill_char);
		}

		static std::string align_right(std::string to_align, std::uint8_t width, char fill_char)
		{
			if (width <= to_align.size())
				return to_align;
			else
				return std::string(width - to_align.size(), fill_char) + to_align;
		}

		static std::string align_center(std::string to_align, std::uint8_t width, char fill_char)
		{
			if (width <= to_align.size()) return to_align;
			else
			{
				std::uint8_t half_width = (width - to_align.size()) / 2;
				if (half_width == 0)
					return std::string(half_width, fill_char) + to_align + std::string(half_width, fill_char);
				else
					return std::string(half_width, fill_char) + to_align +
					std::string(half_width + (width - to_align.size()) % 2, fill_char);
			}
		}
	};
}