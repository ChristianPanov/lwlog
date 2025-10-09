#pragma once

namespace lwlog::details
{
	template<std::size_t Size>
	void sgr_encoder::encode(std::string_view token, memory_buffer<Size>& out)
	{
		std::string_view name{ token };

		bool is_background{ false };
		bool is_dark{ false };

		if (sgr_encoder::has_prefix(name, "bg_"))	{ is_background = true; name.remove_prefix(3); }
		if (sgr_encoder::has_prefix(name, "dark_")) { is_dark		= true; name.remove_prefix(5); }

		const sgr_color_spec* spec{ sgr_encoder::find_color_spec(name) };
		if (!spec)
		{
			return;
		}

		const std::uint8_t code{ sgr_encoder::resolve_color(*spec, is_background, is_dark) };

		char code_digits[3]{};
		std::uint8_t code_digits_count{};
		if (code >= 100)
		{
			code_digits[0] = '1';
			code_digits[1] = '0' + char((code / 10) % 10);
			code_digits[2] = '0' + char(code % 10);
			code_digits_count = 3;
		}
		else
		{
			code_digits[0] = '0' + char(code / 10);
			code_digits[1] = '0' + char(code % 10);
			code_digits_count = 2;
		}

		out.append("\x1b[");
		out.append(code_digits, code_digits_count);
		out.append('m');
	}

	bool sgr_encoder::can_encode(std::string_view token)
	{
		if (sgr_encoder::has_prefix(token, "bg_")) { token.remove_prefix(3); }
		if (sgr_encoder::has_prefix(token, "dark_")) { token.remove_prefix(5); }

		for (const auto& spec : sgr_colors)
		{
			if (spec.base_name == token)
			{
				return true;
			}
		}

		return false;
	}

	bool sgr_encoder::is_base_name_char(unsigned char ch)
	{
		return (ch >= 'a' && ch <= 'z') || ch == '_';
	}

	bool sgr_encoder::has_prefix(std::string_view str, std::string_view prefix)
	{
		return str.compare(0, prefix.size(), prefix) == 0;
	}

	const sgr_color_spec* sgr_encoder::find_color_spec(std::string_view color)
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

	std::uint8_t sgr_encoder::resolve_color(const sgr_color_spec& spec, bool is_background, bool is_dark)
	{
		const std::uint8_t channel_offset{ static_cast<std::uint8_t>(is_background ?
			color_channel_offset::background : color_channel_offset::foreground) };

		if (spec.base_name == "grey")
		{
			const std::uint8_t grey_offset{ static_cast<std::uint8_t>(is_dark ?
				sgr_encoder::intensity_offset - 7 : 0) };
			return spec.fg_base_code + channel_offset + grey_offset;
		}

		if (spec.base_name == "black")
		{
			return spec.fg_base_code + channel_offset;
		}

		const std::uint8_t color_intensity_offset{ static_cast<std::uint8_t>(
			!is_dark ? sgr_encoder::intensity_offset : 0)
		};
		return spec.fg_base_code + channel_offset + color_intensity_offset;
	}
}