#pragma once

namespace lwlog::sinks
{
	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::sink()
	{
		if (!details::terminal::are_colors_supported())
		{
			details::terminal::enable_colors();
		}

		m_pattern.set_pattern("[%d, %T] [%l] [%n]: %v", EnableAnsiColors);
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	bool sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::should_sink(level log_level) const
	{
        const auto filter{ m_level_filter.load(std::memory_order_relaxed) };

		if (level_details::has_level(filter, log_level) 
			|| level_details::has_level(filter, level::all))
		{
			return true;
		}

		return false;
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::set_level_filter(level level_filter)
	{
		lock_t lock(m_mtx);
		m_level_filter.store(level_filter, std::memory_order_relaxed);
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::set_pattern(std::string_view pattern)
	{
		lock_t lock(m_mtx);
		m_pattern.set_pattern(pattern, EnableAnsiColors);
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::add_custom_field(std::string_view name,
		details::custom_value value)
	{
		lock_t lock(m_mtx);
		m_pattern.add_custom_field(name, value);
	}

	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	void sink<EnableAnsiColors, BufferLimits, ThreadingPolicy>::add_custom_field(std::string_view name,
		details::custom_value value, details::custom_format_fn fn)
	{
		lock_t lock(m_mtx);
		m_pattern.add_custom_field(name, value, fn);
	}
}