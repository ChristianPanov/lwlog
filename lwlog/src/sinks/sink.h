#pragma once

#include "level.h"
#include "details/pattern/pattern.h"
#include "policy/sink_color_policy.h"
#include "policy/threading_policy.h"
#include "interface/sink_interface.h"

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
		void add_attribute(details::flag_pair flags, details::attrib_value value) override;
		void set_level_filter(level level) override;
		bool should_sink(level t_level) const override;
		details::pattern& pattern() override;

	private:
		mutable Mutex m_mtx;
		details::pattern m_pattern;
		level m_level{ level::all };
	};
}

#include "sink_impl.h"