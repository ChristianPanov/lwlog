#include "sink.h"

namespace lwlog::sinks
{
	sink::sink()
		: m_pattern("[%d, %x] [%l] [%n]: %v")
	{
		m_levels.emplace_back(sink_level::all);
	}

	void sink::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}

	void sink::set_level_visibility(std::initializer_list<sink_level> level_init_list)
	{
		m_levels.clear();
		m_levels = level_init_list;
	}

	std::string sink::get_pattern() const
	{
		return m_pattern;
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
}