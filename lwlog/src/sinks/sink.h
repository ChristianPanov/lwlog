#pragma once

#include "level.h"
#include "details/pattern/pattern.h"
#include "policy/flush_policy.h"
#include "policy/threading_policy.h"
#include "interface/sink_interface.h"

namespace lwlog::sinks
{
	template<bool EnableAnsiColors, typename ThreadingPolicy>
	class sink : public interface::sink
	{
	private:
		using Mutex = typename ThreadingPolicy::mutex_t;
		using Lock = typename ThreadingPolicy::lock;

	public:
		sink();

	public:
		bool should_sink(level log_level) const override;
		void set_level_filter(level level_filter) override;
		void set_pattern(std::string_view pattern) override;
		void add_attribute(std::string_view flag, details::attrib_value value) override;
		void add_attribute(std::string_view flag, details::attrib_value value, 
			const details::attrib_callback_t& fn) override;

	protected:
		mutable Mutex m_mtx;
		details::pattern m_pattern;
		level m_current_level{ level::all };
		level m_level_filter{ level::all };
	};
}

#include "sink_impl.h"