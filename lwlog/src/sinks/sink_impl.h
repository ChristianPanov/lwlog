#pragma once

namespace lwlog::sinks
{
	template<bool EnableAnsiColors, typename ThreadingPolicy>
	sink<EnableAnsiColors, ThreadingPolicy>::sink()
	{
		if (!details::os::are_ansi_colors_enabled())
		{
			details::os::enable_ansi_colors();
		}

		m_pattern.set_pattern("[%d, %T] [%l] [%n]: %v");
		m_pattern.request_flag_formatters();

		sink::add_attribute(".level(", m_current_level, [&]()
		{
			switch (m_current_level)
			{
				case level::info:		return "\u001b[37m";
				case level::warning:	return "\u001b[33;1m";
				case level::error:		return "\u001b[31;1m";
				case level::critical:	return "\u001b[41;1m";
				case level::debug:		return "\u001b[37;1m";
				case level::all: 		return "";
				case level::none: 		return "";
				default:                return "";
			}
		});
	}

	template<bool EnableAnsiColors, typename ThreadingPolicy>
	bool sink<EnableAnsiColors, ThreadingPolicy>::should_sink(level log_level) const
	{
		Lock lock(m_mtx);
		
		if (level_details::has_level(m_level_filter, log_level) ||
			level_details::has_level(m_level_filter, level::all))
		{
			return true;
		}

		return false;
	}

	template<bool EnableAnsiColors, typename ThreadingPolicy>
	void sink<EnableAnsiColors, ThreadingPolicy>::set_level_filter(level level_filter)
	{
		Lock lock(m_mtx);
		m_level_filter = level_filter;
	}

	template<bool EnableAnsiColors, typename ThreadingPolicy>
	void sink<EnableAnsiColors, ThreadingPolicy>::set_pattern(std::string_view pattern)
	{
		Lock lock(m_mtx);
		m_pattern.set_pattern(pattern);
		m_pattern.parse_alignment_flags();
		m_pattern.request_flag_formatters();
		m_pattern.process_color_flags(EnableAnsiColors);
	}

	template<bool EnableAnsiColors, typename ThreadingPolicy>
	void sink<EnableAnsiColors, ThreadingPolicy>::add_attribute(std::string_view flag,
		details::attrib_value value)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value);
	}

	template<bool EnableAnsiColors, typename ThreadingPolicy>
	void sink<EnableAnsiColors, ThreadingPolicy>::add_attribute(std::string_view flag, details::attrib_value value,
		const details::attrib_callback_t& fn)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value, fn);
	}
}