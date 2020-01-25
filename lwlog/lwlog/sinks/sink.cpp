#include "sink.h"

namespace lwlog::sinks
{
	sink::sink()
		: m_pattern("[%d, %x] [%l] [%n]: %v")
	{}

	void sink::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}
	std::string sink::get_pattern() const
	{
		return m_pattern;
	}
}