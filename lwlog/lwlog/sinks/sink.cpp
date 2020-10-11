#include "sink.h"
#include "sink_level.h"
#include "details/formatter.h"

namespace lwlog::sinks
{
	sink::sink()
		: m_levels{ sink_level::all }
	{}

	void sink::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}

	void sink::add_pattern_attribute(details::pattern_attribute attribute)
	{
		details::formatter::insert_pattern_data({
			{attribute.verbose, attribute.shortened, attribute.attribute }
			});
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

	std::string sink::get_pattern() const
	{
		return m_pattern;
	}
}