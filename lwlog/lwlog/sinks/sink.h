#pragma once

#include <string>

#include "interface/sink_interface.h"
#include "policy/sink_color_policy.h"
#include "fwd.h"

namespace lwlog::sinks
{
	template<typename ColorPolicy = colored_policy>
	class sink : public interface::sink
	{
	public:
		sink();
		virtual ~sink() = default;

	public:
		void set_pattern(std::string_view pattern) override;
		void add_pattern_attribute(primitives::attribute_t attribute) override;
		void set_level_filter(std::initializer_list<sink_level> level_list) override;

		bool should_sink(sink_level t_level) const override;
		std::string pattern() const override;

	private:
		std::string m_pattern;
		std::vector<sink_level> m_levels;
	};
}

#include "sink_impl.h"