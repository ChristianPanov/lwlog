#pragma once

#include "sink.h"

namespace lwlog::sinks
{
	template<typename ColorPolicy, typename ThreadingPolicy>
	sink<ColorPolicy, ThreadingPolicy>::sink()
	{
		m_pattern.set_pattern("[%d, %T] [%l] [%n]: %v");
		m_pattern.request_flag_formatters();
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::set_pattern(std::string_view pattern)
	{
		Lock lock(m_mtx);
		m_pattern.set_pattern(pattern);
		m_pattern.parse_alignment_specs();
		m_pattern.request_flag_formatters();
		m_pattern.process_color_flags(ColorPolicy::is_colored);
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::add_attribute(std::string_view flag,
		details::attrib_value value)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value);
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::add_attribute(std::string_view flag, details::attrib_value value,
		std::function<const char*()> fn)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value, fn);
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::set_level_filter(level level_filter)
	{
		Lock lock(m_mtx);
		m_level_filter = level_filter;
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	bool sink<ColorPolicy, ThreadingPolicy>::should_sink(level t_level) const
	{
		Lock lock(m_mtx);
		if (level_details::has_level(m_level_filter, t_level) ||
			level_details::has_level(m_level_filter, level::all))
			return true;
		return false;
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	details::pattern& sink<ColorPolicy, ThreadingPolicy>::pattern()
	{
		Lock lock(m_mtx);
		return m_pattern;
	}
}