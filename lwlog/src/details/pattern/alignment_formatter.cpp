#include "alignment_formatter.h"

namespace lwlog::details
{
	alignment_info::alignment_info(char fill_char, align_side side, std::uint8_t width, std::string_view flag)
		: fill_char	{ fill_char }
		, side		{ side		}
		, width		{ width		}
		, flag		{ flag		}
	{}

	void alignment_formatter::format(std::string& pattern, const alignment_info& alignment_flag_info)
	{
		constexpr std::size_t flag_end_indicator_size{ 2 };

		const std::size_t flag_size		{ alignment_flag_info.flag.size()								};
		const std::size_t flag_pos		{ pattern.find(alignment_flag_info.flag)						};
		const std::size_t flag_end_pos	{ pattern.find(alignment_info::flag_end, flag_pos + flag_size)	};
		const std::size_t to_align_size	{ flag_end_pos - flag_pos - flag_size							};

		const auto aligned{ alignment_formatter::align(
			pattern.substr(flag_pos + flag_size, to_align_size), 
			alignment_flag_info.width, 
			alignment_flag_info.fill_char, 
			alignment_flag_info.side
		) };

		pattern.replace(flag_pos, to_align_size + flag_size + flag_end_indicator_size, aligned);
	}

	std::string alignment_formatter::align(const std::string& to_align, std::uint8_t width, char fill_char, 
		alignment_info::align_side side)
	{
		switch (side)
		{
		case alignment_info::align_side::left:		return align_left(to_align, width, fill_char);
		case alignment_info::align_side::right:		return align_right(to_align, width, fill_char);
		case alignment_info::align_side::center:	return align_center(to_align, width, fill_char);
		default:									return to_align;
		}
	}

	std::string alignment_formatter::align_left(const std::string& to_align, std::uint8_t width, char fill_char)
	{
		if (width <= to_align.size()) return to_align;

		std::string result;
		result.reserve(width);

		result.append(to_align);
		result.append(width - to_align.size(), fill_char);

		return result;
	}

	std::string alignment_formatter::align_right(const std::string& to_align, std::uint8_t width, char fill_char)
	{
		if (width <= to_align.size()) return to_align;

		std::string result;
		result.reserve(width);

		result.append(width - to_align.size(), fill_char);
		result.append(to_align);

		return result;
	}

	std::string alignment_formatter::align_center(const std::string& to_align, std::uint8_t width, char fill_char)
	{
		if (width <= to_align.size()) return to_align;

		const auto total_padding{ width - to_align.size()		};
		const auto padding_left	{ total_padding / 2				};
		const auto padding_right{ total_padding - padding_left	};

		std::string result;
		result.reserve(width);

		result.append(padding_left, fill_char);
		result.append(to_align);
		result.append(padding_right, fill_char);

		return result;
	}
}
