#pragma once

#include <string>

#include "interface/sink_interface.h"
#include "policy/sink_color_policy.h"
#include "policy/threading_policy.h"
#include "fwd.h"

namespace lwlog::sinks
{
	template<typename ColorPolicy, typename ThreadingPolicy>
	class sink : public interface::sink
	{
	private:
		using Mutex = typename ThreadingPolicy::mutex_t;
		using Lock = typename ThreadingPolicy::lock;

	public:
		sink();
		virtual ~sink() = default;

	public:
		void set_pattern(std::string_view pattern) override;
		void add_pattern_attribute(primitives::attribute_t attribute) override;
		void set_level_filter(level_t level) override;

		bool should_sink(level_t t_level) const override;
		std::string pattern() const override;

	private:
		mutable Mutex m_mtx;
		std::string m_pattern;
		level_t m_level;
	};
}

#include "sink_impl.h"