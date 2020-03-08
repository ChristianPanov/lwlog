#include "sink.h"

namespace lwlog::sinks
{
	sink::sink()
		: m_should_color(true)
		, m_pattern("[%d, %x] [%l] [%n]: %v")
	{
		m_levels.emplace_back(sink_level::all);
	}

	void sink::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}

	void sink::set_level_visibility(std::initializer_list<sink_level> level_list)
	{
		m_levels.clear();
		m_levels = level_list;
	}

	void sink::disable_color()
	{
		m_should_color = false;
	}

	bool sink::should_sink(sink_level level)
	{
		for (const auto& i : m_levels)
		{
			if (level == i || i == sink_level::all)
			{
				return true;
			}
		}

		return false;
	}

	bool sink::should_color()
	{
		return m_should_color;
	}

	std::string sink::get_pattern() const
	{
		return m_pattern;
	}
}