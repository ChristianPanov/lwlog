#pragma once

#include "lwlog/sinks/sink.h"

namespace lwlog::sinks
{
	template<typename ColorPolicy, typename ThreadingPolicy>
	sink<ColorPolicy, ThreadingPolicy>::sink()
		: m_level{ level::all }
		, m_pattern{ "[%d, %T] [%l] [%n]: %v" }
	{}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::set_pattern(std::string_view pattern)
	{
		Lock lock(m_mtx);
		m_pattern = pattern;
		ColorPolicy::process_color(m_pattern);
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
	std::string sink<ColorPolicy, ThreadingPolicy>::pattern() const
	{
		Lock lock(m_mtx);
		return m_pattern;
	}
}
