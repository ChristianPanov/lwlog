#pragma once

namespace lwlog::details::terminal
{
	inline bool sgr_resolver::try_resolve_code(std::string_view token, std::uint8_t& out_code)
	{
		std::string_view name{ token };
		bool is_background{ false };
		bool is_dark{ false };

		if (sgr_resolver::has_prefix(name, "bg_")) { is_background = true; name.remove_prefix(3); }
		if (sgr_resolver::has_prefix(name, "dark_")) { is_dark = true;     name.remove_prefix(5); }

		const sgr_color_spec* spec{ sgr_resolver::find_color_spec(name) };
		if (!spec)
		{
			return false;
		}

		out_code = sgr_resolver::resolve_color(*spec, is_background, is_dark);

		return true;
	}

	inline bool sgr_resolver::is_base_name_char(unsigned char ch)
	{
		return (ch >= 'a' && ch <= 'z') || ch == '_';
	}

	inline bool sgr_resolver::has_prefix(std::string_view str, std::string_view prefix)
	{
		return str.compare(0, prefix.size(), prefix) == 0;
	}

	inline const sgr_color_spec* sgr_resolver::find_color_spec(std::string_view color)
	{
		for (const auto& spec : sgr_colors)
		{
			if (spec.base_name == color)
			{
				return &spec;
			}
		}

		return nullptr;
	}

	inline std::uint8_t sgr_resolver::resolve_color(const sgr_color_spec& spec, bool is_background, bool is_dark)
	{
		const std::uint8_t channel_offset{ static_cast<std::uint8_t>(is_background ?
			color_channel_offset::background : color_channel_offset::foreground) };

		if (spec.base_name == "grey")
		{
			const std::uint8_t grey_offset{ static_cast<std::uint8_t>(is_dark ?
				sgr_resolver::intensity_offset - 7 : 0) };
			return spec.fg_base_code + channel_offset + grey_offset;
		}

		if (spec.base_name == "black")
		{
			return spec.fg_base_code + channel_offset;
		}

		const std::uint8_t color_intensity_offset{ static_cast<std::uint8_t>(
			!is_dark ? sgr_resolver::intensity_offset : 0)
		};
		return spec.fg_base_code + channel_offset + color_intensity_offset;
	}
}