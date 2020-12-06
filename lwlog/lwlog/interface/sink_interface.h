#pragma once

#include "level_filter_interface.h"
#include "pattern_interface.h"

namespace lwlog::interface
{
	class sink : public interface::level_filter, public interface::pattern
	{
	public:
		virtual ~sink() = default;
		virtual void sink_it(std::string_view) = 0;
		virtual bool should_sink(level) const = 0;
		virtual std::string pattern() const = 0;
	};
}