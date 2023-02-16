#include "pattern.h"
#include "format_data.h"
#include "color_format_data.h"

namespace lwlog::details
{
	std::string pattern::compile(const record& record) const
	{
		std::string compiled = m_pattern;
		for (const auto& formatter : m_formatters)
			formatter->format(compiled, record);

		for (const auto& [flags, value] : m_custom_attributes)
			formatter::format_attribute(compiled, flags,
				std::visit(attrib_value_visitor{}, value));

		for (const auto& spec : m_alignment_specs)
			alignment_formatter::format(compiled, spec);

		return compiled;
	}

	void pattern::parse_alignment_specs()
	{
		std::size_t start_pos{ 0 };
		while ((start_pos = m_pattern.find(alignment_flag::left, start_pos)) != std::string::npos)
		{
			const std::size_t flag_pos = m_pattern.find(alignment_flag::left, start_pos);
			m_alignment_specs.emplace_back(
				m_pattern.substr(flag_pos, m_pattern.find(' ', flag_pos) - flag_pos)
			);
			m_pattern.replace(
				m_pattern.find(m_alignment_specs.back().to_align, flag_pos),
				m_alignment_specs.back().to_align.size(),
				m_alignment_specs.back().to_align + alignment_flag::end
			);
			start_pos += 2;
		}

		start_pos = 0;
		while ((start_pos = m_pattern.find(alignment_flag::right, start_pos)) != std::string::npos)
		{
			const std::size_t flag_pos = m_pattern.find(alignment_flag::right, start_pos);
			m_alignment_specs.emplace_back(
				m_pattern.substr(flag_pos, m_pattern.find(' ', flag_pos) - flag_pos)
			);
			m_pattern.replace(
				m_pattern.find(m_alignment_specs.back().to_align, flag_pos),
				m_alignment_specs.back().to_align.size(),
				m_alignment_specs.back().to_align + alignment_flag::end
			);
			start_pos += 2;
		}

		start_pos = 0;
		while ((start_pos = m_pattern.find(alignment_flag::center, start_pos)) != std::string::npos)
		{
			const std::size_t flag_pos = m_pattern.find(alignment_flag::center, start_pos);
			m_alignment_specs.emplace_back(
				m_pattern.substr(flag_pos, m_pattern.find(' ', flag_pos) - flag_pos)
			);
			m_pattern.replace(
				m_pattern.find(m_alignment_specs.back().to_align, flag_pos),
				m_alignment_specs.back().to_align.size(),
				m_alignment_specs.back().to_align + alignment_flag::end
			);
			start_pos += 2;
		}
	}

	void pattern::request_flag_formatters()
	{
		const auto verbose_flags = this->parse_verbose_flags();
		const auto short_flags = this->parse_short_flags();

		for (const auto& flag : verbose_flags)
			if (verbose_data[flag])
				m_formatters.push_back(verbose_data[flag]);

		for (const auto& flag : short_flags)
			if (shortened_data[flag])
				m_formatters.push_back(shortened_data[flag]);
	}

	void pattern::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}

	void pattern::add_attribute(const flag_pair& flags, attrib_value value)
	{
		m_custom_attributes.push_back({ flags, value });
	}

	std::string& pattern::data()
	{
		return m_pattern;
	}

	void pattern::compile_colors(std::string& pattern)
	{
		if (std::strchr(pattern.data(), '.'))
		{
			while (std::strchr(pattern.data(), ')'))
				pattern.replace(pattern.find(')'), 1, "\u001b[0m");

			for (const auto& [key, value] : color_data)
				while (std::strstr(pattern.data(), key.data()))
					pattern.replace(pattern.find(key), key.length(), value);
		}
	}

	void pattern::drop_color_flags(std::string& pattern)
	{
		if (std::strchr(pattern.data(), '.'))
		{
			while (std::strchr(pattern.data(), ')'))
				pattern.replace(pattern.find(')'), 1, "");

			for (const auto& [key, value] : color_data)
				while (std::strstr(pattern.data(), key.data()))
					pattern.replace(pattern.find(key), key.length(), "");
		}
	}

	std::vector<std::string> pattern::parse_verbose_flags() const
	{
		std::vector<std::string> temp;
		std::size_t pos = m_pattern.find('{', 0);
		while (pos != std::string::npos)
		{
			temp.emplace_back(m_pattern.substr(pos, m_pattern.find('}', pos) - pos + 1));
			pos = m_pattern.find('{', pos + 1);
		}
		return temp;
	}

	std::vector<std::string> pattern::parse_short_flags() const
	{
		std::vector<std::string> temp;
		std::size_t pos = m_pattern.find('%', 0);
		while (pos != std::string::npos)
		{
			temp.emplace_back(m_pattern.substr(pos, 2));
			pos = m_pattern.find('%', pos + 1);
		}
		return temp;
	}
}