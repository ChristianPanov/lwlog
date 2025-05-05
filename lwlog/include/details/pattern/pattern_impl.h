#pragma once

#include "pattern.h"
#include "color_format_data.h"
#include "formatters.h"

namespace lwlog::details
{
	template<typename Config, typename BufferLimits>
	const char* pattern<Config, BufferLimits>::compile(const details::record<Config, BufferLimits>& record)
	{
		for (const auto& formatter : m_formatters)
			formatter->format(m_pattern_buffer, m_conv_buffer, record);

		for (const auto& attribute : m_attributes)
			formatter<Config, BufferLimits>::format_custom_attribute(m_pattern_buffer, m_conv_buffer, attribute);

		for (const auto& info : m_alignment_flags_info)
			alignment_formatter<BufferLimits>::format(m_pattern_buffer, m_padding_buffer, info);

		return m_pattern_buffer.c_str();
	}

	template<typename Config, typename BufferLimits>
	void pattern<Config, BufferLimits>::parse_alignment_flags()
	{
		std::size_t flag_start_pos{ 0 };
		while ((flag_start_pos = m_pattern_buffer.data().find_first_of("<>^", flag_start_pos)) != std::string::npos)
		{
			flag_start_pos -= 1;

			const std::string_view pattern_view{ m_pattern_buffer.data() };
			const std::size_t flag_end_pos{ pattern_view.find(' ', flag_start_pos) };
			const std::string_view flag_view{ pattern_view.data() + flag_start_pos, flag_end_pos - flag_start_pos };

			const bool has_fill_char{ !std::isdigit(flag_view[2]) };
			const std::uint8_t flag_length{ static_cast<std::uint8_t>(has_fill_char ? 3U : 2U) };

			const std::string_view width_str{ flag_view.data() + flag_length,
				std::isdigit(flag_view[flag_length + 1]) ? static_cast<std::size_t>(2) : static_cast<std::size_t>(1) };

			const char fill_char{ has_fill_char ? flag_view[2] : ' ' };
			const std::uint8_t width{ static_cast<std::uint8_t>(std::stoi(width_str.data())) };
			const alignment_info::align_side align_side{ static_cast<std::uint8_t>(flag_view[1]) };
			const std::string_view flag{ flag_view.data(), flag_length + width_str.size() };

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

	template<typename Config, typename BufferLimits>
	void pattern<Config, BufferLimits>::request_flag_formatters()
	{
		const auto& verbose_flags{ this->parse_verbose_flags() };
		const auto& short_flags{ this->parse_short_flags() };

		for (const auto flag : verbose_flags)
		{
			auto formatter{ this->flag_to_formatter(flag) };
			if (formatter)
			{
				m_formatters.push_back(std::move(formatter));
			}
		}

		for (const auto flag : short_flags)
		{
			auto formatter{ this->flag_to_formatter(flag) };
			if (formatter)
			{
				m_formatters.push_back(std::move(formatter));
			}
		}
	}

	template<typename Config, typename BufferLimits>
	void pattern<Config, BufferLimits>::process_color_flags(bool use_color)
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

	template<typename Config, typename BufferLimits>
	void pattern<Config, BufferLimits>::cache_pattern()
	{
		std::memcpy(m_cached_pattern_buffer, m_pattern_buffer.c_str(), m_pattern_buffer.size());
	}

	template<typename Config, typename BufferLimits>
	void pattern<Config, BufferLimits>::reset_pattern()
	{
		m_pattern_buffer.reset();
		m_pattern_buffer.append(m_cached_pattern_buffer);
	}

	template<typename Config, typename BufferLimits>
	void pattern<Config, BufferLimits>::set_pattern(std::string_view pattern)
	{
		m_formatters.clear();
		m_pattern_buffer.reset();
		m_pattern_buffer.append(pattern);
		m_pattern_buffer.append('\n');
	}

	template<typename Config, typename BufferLimits>
	void pattern<Config, BufferLimits>::add_attribute(std::string_view flag, attrib_value value)
	{
		m_attributes.emplace_back(flag, value);
	}

	template<typename Config, typename BufferLimits>
	void pattern<Config, BufferLimits>::add_attribute(std::string_view flag, attrib_value value, const attrib_callback_t& fn)
	{
		m_attributes.emplace_back(flag, value, fn);
	}

	template<typename Config, typename BufferLimits>
	std::unique_ptr<formatter<Config, BufferLimits>> pattern<Config, BufferLimits>::flag_to_formatter(std::string_view flag) const
	{
		if (flag == flag::level.verbose || flag == flag::level.shortened)
		{
			return std::make_unique<level_formatter<Config, BufferLimits>>();
		}
		else if (flag == flag::message.verbose || flag == flag::message.shortened)
		{
			return std::make_unique<message_formatter<Config, BufferLimits>>();
		}
		else if (flag == flag::thread_id.verbose || flag == flag::thread_id.shortened)
		{
			return std::make_unique<thread_id_formatter<Config, BufferLimits>>();
		}
		else if (flag == flag::process_id.verbose || flag == flag::process_id.shortened)
        {
            return std::make_unique<process_id_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::line.verbose || flag == flag::line.shortened)
        {
            return std::make_unique<line_formatter<Config, BufferLimits>>();
        }
		else if (flag == flag::path.verbose || flag == flag::path.shortened)
		{
			return std::make_unique<path_formatter<Config, BufferLimits>>();
		}
        else if (flag == flag::file.verbose || flag == flag::file.shortened)
        {
            return std::make_unique<file_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::function.verbose || flag == flag::function.shortened)
        {
            return std::make_unique<function_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::topic.verbose || flag == flag::topic.shortened)
        {
            return std::make_unique<topic_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::full_topic.verbose || flag == flag::full_topic.shortened)
        {
            return std::make_unique<full_topic_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::date.verbose || flag == flag::date.shortened)
        {
            return std::make_unique<date_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::date_short.verbose || flag == flag::date_short.shortened)
        {
            return std::make_unique<date_short_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::year.verbose || flag == flag::year.shortened)
        {
            return std::make_unique<year_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::year_short.verbose || flag == flag::year_short.shortened)
        {
            return std::make_unique<year_short_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::month.verbose || flag == flag::month.shortened)
        {
            return std::make_unique<month_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::month_name.verbose || flag == flag::month_name.shortened)
        {
            return std::make_unique<month_name_formatter<Config, BufferLimits>>();
        }
		else if (flag == flag::month_name_short.verbose || flag == flag::month_name_short.shortened)
        {
            return std::make_unique<month_name_short_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::day.verbose || flag == flag::day.shortened)
        {
            return std::make_unique<day_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::weekday.verbose || flag == flag::weekday.shortened)
        {
            return std::make_unique<weekday_name_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::weekday_short.verbose || flag == flag::weekday_short.shortened)
        {
            return std::make_unique<weekday_name_short_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::time.verbose || flag == flag::time.shortened)
        {
            return std::make_unique<time_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::hour_clock_24.verbose || flag == flag::hour_clock_24.shortened)
        {
            return std::make_unique<hour_clock_24_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::hour_clock_12.verbose || flag == flag::hour_clock_12.shortened)
        {
            return std::make_unique<hour_clock_12_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::ampm.verbose || flag == flag::ampm.shortened)
        {
            return std::make_unique<ampm_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::hour_24.verbose || flag == flag::hour_24.shortened)
        {
            return std::make_unique<hour_24_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::hour_12.verbose || flag == flag::hour_12.shortened)
        {
            return std::make_unique<hour_12_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::minute.verbose || flag == flag::minute.shortened)
        {
            return std::make_unique<minute_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::second.verbose || flag == flag::second.shortened)
        {
            return std::make_unique<second_formatter<Config, BufferLimits>>();
        }
		else if (flag == flag::millisecond.verbose || flag == flag::millisecond.shortened)
        {
            return std::make_unique<millisecond_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::microsecond.verbose || flag == flag::microsecond.shortened)
        {
            return std::make_unique<microsecond_formatter<Config, BufferLimits>>();
        }
        else if (flag == flag::nanosecond.verbose || flag == flag::nanosecond.shortened)
        {
            return std::make_unique<nanosecond_formatter<Config, BufferLimits>>();
        }

		return nullptr;
	}

	template<typename Config, typename BufferLimits>
	std::vector<std::string_view> pattern<Config, BufferLimits>::parse_verbose_flags()
	{
		const std::string_view pattern_view{ m_pattern_buffer.data() };

		std::vector<std::string_view> flags;
		flags.reserve(std::count(pattern_view.begin(), pattern_view.end(), '{'));

		std::size_t flag_start_pos{ 0 };
		while ((flag_start_pos = pattern_view.find('{', flag_start_pos)) != std::string_view::npos)
		{
			const std::size_t flag_end_pos{ pattern_view.find('}', flag_start_pos + 1) };
			const std::size_t flag_size{ flag_end_pos - flag_start_pos + 1 };

			flags.emplace_back(pattern_view.data() + flag_start_pos, flag_size);
			flag_start_pos = pattern_view.find('{', flag_start_pos + 1);
		}
		return flags;
	}

	template<typename Config, typename BufferLimits>
	std::vector<std::string_view> pattern<Config, BufferLimits>::parse_short_flags()
	{
		constexpr std::uint8_t flag_size{ 2 };
		const std::string_view pattern_view{ m_pattern_buffer.data() };

		std::vector<std::string_view> flags;
		flags.reserve(pattern_view.size() / flag_size);

		std::size_t flag_start_pos{ 0 };
		while ((flag_start_pos = pattern_view.find('%', flag_start_pos)) != std::string_view::npos)
		{
			flags.emplace_back(pattern_view.data() + flag_start_pos, flag_size);
			flag_start_pos += flag_size;
		}
		return flags;
	}
}