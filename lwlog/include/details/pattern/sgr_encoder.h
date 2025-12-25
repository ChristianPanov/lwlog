#pragma once

#include <cstdint>

#include "details/memory_buffer.h"

namespace lwlog::details
{
	struct sgr_color_spec
	{
		std::string_view base_name;
		std::uint8_t fg_base_code;
	};

	constexpr inline sgr_color_spec sgr_colors[] =
	{
		{ "black",		30 },
		{ "white",		37 },
		{ "grey",		37 },
		{ "red",		31 },
		{ "green",		32 },
		{ "yellow",		33 },
		{ "blue",		34 },
		{ "magenta",	35 },
		{ "cyan",		36 }
	};

	class sgr_encoder
	{
		enum class color_channel_offset { foreground = 0, background = 10 };
		static constexpr std::uint8_t intensity_offset{ 60 };

	public:
		static constexpr const char* reset{ "\x1b[0m" };

	public:
		template<std::size_t Size>
		static void encode(std::string_view token, memory_buffer<Size>& out);

		static bool can_encode(std::string_view token);

	public:
		static bool is_base_name_char(unsigned char ch);

	private:
		static bool has_prefix(std::string_view str, std::string_view prefix);
		static const sgr_color_spec* find_color_spec(std::string_view color);
		static std::uint8_t resolve_color(const sgr_color_spec&, bool is_background, bool is_dark);
	};
}

#include "sgr_encoder_impl.h"