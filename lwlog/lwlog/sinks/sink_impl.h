#pragma once

#include "sink.h"
#include "sink_level.h"
#include "details/formatter/formatter.h"

namespace lwlog::sinks
{
	template<typename ColorPolicy>
	sink<ColorPolicy>::sink()
		: m_levels{ sink_level::all }
		, m_pattern{ "[%d, %T] [%l] [%n]: %v" }
	{}

	template<typename ColorPolicy>
	void sink<ColorPolicy>::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
		ColorPolicy::process_color(m_pattern);
	}

	template<typename ColorPolicy>
	void sink<ColorPolicy>::add_pattern_attribute(primitives::attribute_t attribute)
	{
		details::formatter::insert_pattern_data({ attribute });
	}

	template<typename ColorPolicy>
	void sink<ColorPolicy>::set_level_filter(std::initializer_list<sink_level> level_list)
	{
		m_levels.clear();
		m_levels = level_list;
	}

	template<typename ColorPolicy>
	bool sink<ColorPolicy>::should_sink(sink_level t_level) const
	{
		for (const auto& level : m_levels)
		{
			if (t_level == level || level == sink_level::all)
			{
				return true;
			}
		}

		return false;
	}

	template<typename ColorPolicy>
	std::string sink<ColorPolicy>::pattern() const
	{
		return m_pattern;
	}
}