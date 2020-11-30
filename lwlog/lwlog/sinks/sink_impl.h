#pragma once

#include "sink.h"
#include "sink_level.h"
#include "details/formatter/formatter.h"

namespace lwlog::sinks
{
	template<typename ColorPolicy, typename ThreadingPolicy>
	sink<ColorPolicy, ThreadingPolicy>::sink()
		: m_levels{ sink_level::all }
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
	void sink<ColorPolicy, ThreadingPolicy>::set_level_filter(primitives::level_list levels)
	{
		Lock lock(m_mtx);
		m_levels.clear();
		m_levels = levels;
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	bool sink<ColorPolicy, ThreadingPolicy>::should_sink(sink_level t_level) const
	{
		Lock lock(m_mtx);
		for (const auto& level : m_levels)
		{
			if (t_level == level || level == sink_level::all)
			{
				return true;
			}
		}

		return false;
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	std::string sink<ColorPolicy, ThreadingPolicy>::pattern() const
	{
		Lock lock(m_mtx);
		return m_pattern;
	}
}