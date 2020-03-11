#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../core.h"
#include "sink_level.h"

namespace lwlog::sinks
{
	class LWLOG_API sink
	{
	public:
		sink();
		virtual ~sink() = default;

		virtual void sink_it(std::string_view) = 0;

	public:
		void set_pattern(std::string_view pattern);
		void set_level_visibility(std::initializer_list<sink_level> level_list);
		void disable_color();
		bool should_sink(sink_level level) const;
		bool should_color() const;
		std::string get_pattern() const;

	protected:
		bool m_should_color;
		std::string m_pattern;
		std::vector<sink_level> m_levels;
	};

	using sink_ptr = std::shared_ptr<sink>;
}