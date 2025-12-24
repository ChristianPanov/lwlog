#pragma once

namespace lwlog::sinks
{
	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::sink()
	{
		if (!details::os::are_ansi_colors_enabled())
		{
			details::os::enable_ansi_colors();
		}

		m_pattern.set_pattern("[%d, %T] [%l] [%n]: %v", EnableAnsiColors);
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	bool sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::should_sink(level log_level) const
	{
		Lock lock(m_mtx);
		
		if (level_details::has_level(m_level_filter, log_level) ||
			level_details::has_level(m_level_filter, level::all))
		{
			return true;
		}

		return false;
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::set_level_filter(level level_filter)
	{
		Lock lock(m_mtx);
		m_level_filter = level_filter;
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::set_pattern(std::string_view pattern)
	{
		Lock lock(m_mtx);
		m_pattern.set_pattern(pattern, EnableAnsiColors);
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::add_attribute(std::string_view flag,
		details::custom_value value)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value);
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::add_attribute(std::string_view flag, 
		details::custom_value value, const details::custom_format_fn& fn)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value, fn);
	}
}