#pragma once

#include "sink.h"

namespace lwlog::sinks
{
	template<typename ColorPolicy, typename ThreadingPolicy>
	sink<ColorPolicy, ThreadingPolicy>::sink()
	{
		if (!details::os::are_ansi_colors_enabled()) 
			details::os::enable_ansi_colors();

		m_pattern.set_pattern("[%d, %T] [%l] [%n]: %v");
		m_pattern.request_flag_formatters();

		this->add_attribute(".level(", m_current_level, [&]() -> const char*
		{
			switch (m_current_level)
			{
				case level::info:		return "\u001b[37m";
				case level::warning:	return "\u001b[33;1m";
				case level::error:		return "\u001b[31;1m";
				case level::critical:	return "\u001b[41;1m";
				case level::debug:		return "\u001b[37;1m";
			}
		});
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::set_pattern(std::string_view pattern)
	{
		Lock lock(m_mtx);
		m_pattern.set_pattern(pattern);
		m_pattern.parse_alignment_specs();
		m_pattern.request_flag_formatters();
		m_pattern.process_color_flags(ColorPolicy::is_colored);
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::add_attribute(std::string_view flag,
		details::attrib_value value)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value);
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::add_attribute(std::string_view flag, details::attrib_value value,
		details::attrib_callback_t fn)
	{
		Lock lock(m_mtx);
		m_pattern.add_attribute(flag, value, fn);
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	void sink<ColorPolicy, ThreadingPolicy>::set_level_filter(level level_filter)
	{
		Lock lock(m_mtx);
		m_level_filter = level_filter;
	}

	template<typename ColorPolicy, typename ThreadingPolicy>
	bool sink<ColorPolicy, ThreadingPolicy>::should_sink(level t_level) const
	{
		Lock lock(m_mtx);
		if (level_details::has_level(m_level_filter, t_level) ||
			level_details::has_level(m_level_filter, level::all))
			return true;
		return false;
	}
}