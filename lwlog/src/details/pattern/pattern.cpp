#include "pattern.h"
#include "format_data.h"
#include "color_format_data.h"

namespace lwlog::details
{
	std::string pattern::compile(const record_base& record)
	{
		for (const auto& formatter : m_formatters)
			formatter->format(m_pattern_buffer, record);

		for (const auto& attribute : m_attributes)
			formatter::format_custom_attribute(m_pattern_buffer, attribute);

		for (const auto& info : m_alignment_flags_info)
			alignment_formatter::format(m_pattern_buffer, info);

		return m_pattern_buffer.c_str();
	}

	void pattern::parse_alignment_flags()
	{
		std::size_t flag_start_pos{ 0 };
		while ((flag_start_pos = m_pattern_buffer.data().find_first_of("<>^", flag_start_pos)) != std::string::npos)
		{
			flag_start_pos -= 1;

			const std::string_view pattern_view{ m_pattern_buffer.data() };
			const std::size_t flag_end_pos{ pattern_view.find(' ', flag_start_pos) };
			const std::string_view flag_view{ pattern_view.substr(flag_start_pos, flag_end_pos - flag_start_pos) };

			const bool has_fill_char{ !std::isdigit(flag_view[2]) };
			const std::uint8_t flag_length{ static_cast<std::uint8_t>(has_fill_char ? 3U : 2U) };

			const std::string_view width_str{ flag_view.substr(flag_length,
				std::isdigit(flag_view[flag_length + 1]) ? 2 : 1) };

			const char fill_char{ has_fill_char ? flag_view[2] : ' ' };
			const std::uint8_t width{ static_cast<std::uint8_t>(std::stoi(width_str.data())) };
			const alignment_info::align_side align_side{ static_cast<std::uint8_t>(flag_view[1]) };
			const std::string_view flag{ flag_view.substr(0, flag_length + width_str.size()) };

			m_alignment_flags_info.emplace_back(fill_char, align_side, width, flag);

			std::string_view to_align;
			if (const std::size_t short_flag_pos{ flag_view.find('%') };
				short_flag_pos != std::string_view::npos)
			{
				to_align = flag_view.substr(short_flag_pos, 2);
			}
			else if (const std::size_t verbose_flag_pos{ flag_view.find('{') };
				verbose_flag_pos != std::string_view::npos)
			{
				to_align = flag_view.substr(verbose_flag_pos,
					flag_view.find('}', verbose_flag_pos) - verbose_flag_pos + 1);
			}

			m_pattern_buffer.insert(pattern_view.find(to_align, flag_start_pos) + to_align.size(),
                2, alignment_info::flag_end);

			flag_start_pos += to_align.size();
		}
	}

	void pattern::request_flag_formatters()
	{
		const auto& verbose_flags{ this->parse_verbose_flags() };
		const auto& short_flags{ this->parse_short_flags() };

		for (const auto flag : verbose_flags)
		{
			if (const auto it{ verbose_data.find(flag) }; 
				it != verbose_data.end())
			{
				m_formatters.push_back(it->second);
			}
		}

		for (const auto flag : short_flags)
		{
			if (const auto it{ shortened_data.find(flag) }; 
				it != shortened_data.end())
			{
				m_formatters.push_back(it->second);
			}
		}
	}

	void pattern::process_color_flags(bool use_color)
	{
		const char* const reset_seq{ use_color ? "\u001b[0m" : "" };
		const std::uint8_t reset_seq_len{ use_color ? 
			static_cast<std::uint8_t>(4) : 
			static_cast<std::uint8_t>(0) 
		};

		std::size_t pos{ 0 };
		while (pos < m_pattern_buffer.size())
		{
			if (m_pattern_buffer[pos] == '.')
			{
				const std::size_t color_seq_end_pos{ m_pattern_buffer.data().find("(", pos) };
				const std::string_view color_flag{ m_pattern_buffer.c_str() + pos, color_seq_end_pos - pos + 1 };

				if (const auto it = color_data.find(color_flag); it != color_data.end())
				{
					const char* const color_seq{ use_color ? it->second.data() : "" };
					const std::size_t color_seq_len{ use_color ? it->second.size() : 0 };

					m_pattern_buffer.replace(pos, color_seq_end_pos - pos + 1, color_seq, color_seq_len);
					pos += color_seq_len;
				}
				else
				{
					++pos;
				}
			}
			else if (m_pattern_buffer[pos] == ')')
			{
				m_pattern_buffer.replace(pos, 1, reset_seq, reset_seq_len);
				pos += reset_seq_len;
			}
			else
			{
				++pos;
			}
		}
	}

	void pattern::save_pattern_state()
	{
		std::memcpy(m_chached_pattern, m_pattern_buffer.c_str(), m_pattern_buffer.size());
	}

	void pattern::reset_pattern()
	{
		m_pattern_buffer.reset();
		m_pattern_buffer.append(m_chached_pattern);
	}

	void pattern::set_pattern(std::string_view pattern)
	{
		m_pattern_buffer.reset();
		m_pattern_buffer.append(pattern);
		m_pattern_buffer.append('\n');
	}

	void pattern::add_attribute(std::string_view flag, attrib_value value)
	{
		m_attributes.emplace_back(flag, value);
	}

	void pattern::add_attribute(std::string_view flag, attrib_value value, const attrib_callback_t& fn)
	{
		m_attributes.emplace_back(flag, value, fn);
	}

	std::vector<std::string_view> pattern::parse_verbose_flags() const
	{
		const std::string_view pattern_view{ m_pattern_buffer.data() };

		std::vector<std::string_view> flags;
		flags.reserve(std::count(pattern_view.begin(), pattern_view.end(), '{'));

		std::size_t flag_start_pos{ 0 };
		while ((flag_start_pos = pattern_view.find('{', flag_start_pos)) != std::string_view::npos)
		{
			const std::size_t flag_end_pos{ pattern_view.find('}', flag_start_pos + 1) };
			const std::size_t flag_size{ flag_end_pos - flag_start_pos + 1 };

			flags.emplace_back(pattern_view.substr(flag_start_pos, flag_size));
			flag_start_pos = pattern_view.find('{', flag_start_pos + 1);
		}
		return flags;
	}

	std::vector<std::string_view> pattern::parse_short_flags() const
	{
		constexpr std::uint8_t flag_size{ 2 };
		const std::string_view pattern_view{ m_pattern_buffer.data() };

		std::vector<std::string_view> flags;
		flags.reserve(pattern_view.size() / flag_size);

		std::size_t flag_start_pos{ 0 };
		while ((flag_start_pos = pattern_view.find('%', flag_start_pos)) != std::string_view::npos)
		{
			flags.emplace_back(pattern_view.substr(flag_start_pos, flag_size));
			flag_start_pos += flag_size;
		}
		return flags;
	}
}