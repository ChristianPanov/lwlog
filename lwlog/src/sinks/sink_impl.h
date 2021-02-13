#pragma once

#include "sink.h"

namespace lwlog::sinks
{
	template<typename ColorPolicy, typename ThreadingPolicy>
	sink<ColorPolicy, ThreadingPolicy>::sink()
	{
		m_pattern.set_pattern("[%d, %T] [%l] [%n]: %v");
		m_pattern.handle_flag_formatters();
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::set_pattern(std::string_view pattern)
	{
		Lock lock(m_mtx);
		m_pattern.set_pattern(pattern);
		m_pattern.handle_flag_formatters();
		ColorPolicy::process_color(m_pattern.data());
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::set_level_filter(level level)
	{
		Lock lock(m_mtx);
		m_level = level;
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	bool sink<ColorPolicy, ThreadingPolicy>::should_sink(level t_level) const
	{
		Lock lock(m_mtx);
		if (level_details::value(m_level) & level_details::value(t_level)) return true;
		else if (level_details::value(m_level) & level_details::value(level::all)) return true;
		return false;
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	details::pattern& sink<ColorPolicy, ThreadingPolicy>::pattern()
	{
		Lock lock(m_mtx);
		return m_pattern;
	}
}