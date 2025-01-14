#pragma once

namespace lwlog::sinks
{
	template<bool EnableAnsiColors, typename Config, typename BufferLimits, typename ThreadingPolicy>
	sink<EnableAnsiColors, Config, BufferLimits, ThreadingPolicy>::sink()
	{
		if (!details::os::are_ansi_colors_enabled())
		{
			details::os::enable_ansi_colors();
		}

		m_pattern.set_pattern("[%d, %T] [%l] [%n]: %v");
		m_pattern.request_flag_formatters();

		sink::add_attribute(".level(", m_current_level, [&](char* buffer, std::size_t size)
		{
			switch (m_current_level)
			{
			case level::info:		buffer = "\u001b[37m"; break;
			case level::warning:	buffer = "\u001b[33;1m"; break;
			case level::error:		buffer = "\u001b[31;1m"; break;
			case level::critical:	buffer = "\u001b[41;1m"; break;
			case level::debug:		buffer = "\u001b[37;1m"; break;
			case level::all: 		buffer = ""; break;
			case level::none: 		buffer = ""; break;
			}
		});
	}

	template<bool EnableAnsiColors, typename Config, typename BufferLimits, typename ThreadingPolicy>
	bool sink<EnableAnsiColors, Config, BufferLimits, ThreadingPolicy>::should_sink(level log_level) const
	{
		Lock lock(m_mtx);
		
		if (level_details::has_level(m_level_filter, log_level) ||
			level_details::has_level(m_level_filter, level::all))
		{
			return true;
		}

		return false;
	}

	template<bool EnableAnsiColors, typename Config, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, Config, BufferLimits, ThreadingPolicy>::set_level_filter(level level_filter)
	{
		Lock lock(m_mtx);
		m_level_filter = level_filter;
	}

	template<bool EnableAnsiColors, typename Config, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, Config, BufferLimits, ThreadingPolicy>::set_pattern(std::string_view pattern)
	{
		Lock lock(m_mtx);
		m_pattern.set_pattern(pattern);
		m_pattern.parse_alignment_flags();
		m_pattern.request_flag_formatters();
		m_pattern.process_color_flags(EnableAnsiColors);
		m_pattern.cache_pattern();
	}

	template<bool EnableAnsiColors, typename Config, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, Config, BufferLimits, ThreadingPolicy>::add_attribute(std::string_view flag,
		details::attrib_value value)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value);
	}

	template<bool EnableAnsiColors, typename Config, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, Config, BufferLimits, ThreadingPolicy>::add_attribute(std::string_view flag, 
		details::attrib_value value, const details::attrib_callback_t& fn)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value, fn);
	}
}