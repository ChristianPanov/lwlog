#include "sink.h"
#include "sink_level.h"
#include "details/formatter.h"

namespace lwlog::sinks
{
	sink::sink()
		: m_levels{ sink_level::all }
		, m_pattern{ "[%d, %T] [%l] [%n]: %v" }
	{}

	void sink::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}

	void sink::add_pattern_attribute(primitives::attribute_t attribute)
	{
		details::formatter::insert_pattern_data({ attribute });
	}

	void sink::set_level_filter(std::initializer_list<sink_level> level_list)
	{
		m_levels.clear();
		m_levels = level_list;
	}

	void sink::disable_color()
	{
		m_should_color = false;
	}

	bool sink::should_color() const
	{
		return m_should_color;
	}

	bool sink::should_sink(sink_level t_level) const
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

	std::string sink::pattern() const
	{
		return m_pattern;
	}
}