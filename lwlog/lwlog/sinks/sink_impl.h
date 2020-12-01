#pragma once

#include "sink.h"
#include "level.h"
#include "details/formatter/formatter.h"

namespace lwlog::sinks
{
	template<typename ColorPolicy, typename ThreadingPolicy>
	sink<ColorPolicy, ThreadingPolicy>::sink()
		: m_level{ level_t::all }
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
	void sink<ColorPolicy, ThreadingPolicy>::add_pattern_attribute(primitives::attribute_t attribute)
	{
		Lock lock(m_mtx);
		details::formatter::insert_pattern_data({ attribute });
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::set_level_filter(level_t level)
	{
		Lock lock(m_mtx);
		m_level = level;
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	bool sink<ColorPolicy, ThreadingPolicy>::should_sink(level_t t_level) const
	{
		Lock lock(m_mtx);
		if (level::level_value(m_level) & level::level_value(t_level)) return true;
		else if (level::level_value(m_level) & level::level_value(level_t::all)) return true;
		return false;
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	std::string sink<ColorPolicy, ThreadingPolicy>::pattern() const
	{
		Lock lock(m_mtx);
		return m_pattern;
	}
}