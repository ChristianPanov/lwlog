#include "sink.h"

namespace lwlog::sinks
{
	sink::sink()
		: m_pattern("[%d, %x] [%l] [%n]: %v")
		, m_level(level::all)
	{
		set_level_visibility(m_level);
	}

	void sink::set_level_visibility(level log_level)
	{
		if (log_level == level::all) 
		{
			m_level = level::info | level::warning
				| level::error | level::critical | level::debug;
		}
		else if (log_level == level::none) 
		{
			m_level = level::none;
		}
		else 
		{
			m_level = log_level;
		}
	}

	void sink::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}
}