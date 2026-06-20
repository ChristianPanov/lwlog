#pragma once

#include "level.h"
#include "details/terminal/terminal.h"
#include "details/pattern/pattern.h"
#include "policy/flush_policy.h"
#include "policy/threading_policy.h"
#include "sink_interface.h"

namespace lwlog::sinks
{
	template<bool EnableAnsiColors, typename BufferLimits, typename ThreadingPolicy>
	class sink : public interface::sink
	{
	private:
		template<typename T>
        using atomic_t = typename ThreadingPolicy::template atomic_t<T>;
		using mutex_t = typename ThreadingPolicy::mutex_t;
		using lock_t = typename ThreadingPolicy::lock_t;

	public:
		sink();

	public:
		bool should_sink(level log_level) const override;
		void set_level_filter(level level_filter) override;
		void set_pattern(std::string_view pattern) override;
		void add_custom_field(std::string_view name, details::custom_value value) override;
		void add_custom_field(std::string_view name, details::custom_value value, details::custom_format_fn fn) override;

	protected:
		mutable mutex_t m_mtx;
		details::pattern<BufferLimits> m_pattern;
		atomic_t<level> m_level_filter{ level::all };
	};
}

#include "sink_impl.h"