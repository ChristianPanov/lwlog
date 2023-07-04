#pragma once

#include "logger.h"
#include "sinks/sink_factory.h"
#include "registry.h"

namespace lwlog
{
	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	template<typename... SinkParams>
	logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name, SinkParams&&... params)
		: m_name{ name }
	{
		if(registry::instance().is_registry_automatic())
			registry::instance().register_logger(this);

		m_sink_storage = { sinks::sink_factory<Sinks<ThreadingPolicy>>::request(
			std::forward<SinkParams>(params)...
		)... };

		this->add_attribute("{name}", m_name);
		this->add_attribute("%n", m_name);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	template<typename Iterator, typename... SinkParams>
	logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		Iterator begin, Iterator end, SinkParams&&... params)
		: logger{ name, params... }
	{
		StoragePolicy<Sinks<ThreadingPolicy>...>::insert_range(m_sink_storage, begin, end);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	template<typename... SinkParams>
	logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		sink_list sink_list, SinkParams&&... params)
		: logger{ name, sink_list.begin(), sink_list.end(), params... }
	{}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	template<typename... SinkParams>
	logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		sink_ptr sink, SinkParams&&... params)
		: logger{ name, { sink }, params... }
	{}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::add_sink(sink_ptr sink)
	{
		StoragePolicy<Sinks<ThreadingPolicy>...>::add_sink(m_sink_storage, sink);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::remove_sink(sink_ptr sink)
	{
		StoragePolicy<Sinks<ThreadingPolicy>...>::remove_sink(m_sink_storage, sink);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::sink_logs()
	{
		LogPolicy::sink_logs();
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::set_pattern(std::string_view pattern)
	{
		for (const auto& sink : m_sink_storage)
		{ 
			sink->set_pattern(pattern);
		}
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
		void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::add_attribute(std::string_view flag,
			details::attrib_value value)
	{
		for (const auto& sink : m_sink_storage)
		{
			sink->add_attribute(flag, value);
		}
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
		void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::add_attribute(std::string_view flag,
			details::attrib_value value, details::attrib_callback_t fn)
	{
		for (const auto& sink : m_sink_storage)
		{
			sink->add_attribute(flag, value, fn);
		}
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::set_level_filter(level t_level)
	{
		for (const auto& sink : m_sink_storage)
		{
			sink->set_level_filter(t_level);
		}
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	std::string_view logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::name() const
	{
		return m_name;
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	typename logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::Storage&
		logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::sinks()
	{
		return m_sink_storage;
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::log(const details::log_message& log_msg,
		level t_level, details::format_args_list args)
	{
		for (const auto& sink : m_sink_storage)
		{
			if (sink->should_sink(t_level))
			{
				LogPolicy::log(sink, { LWLOG_FORMAT_FN(log_msg.message, args), t_level, log_msg.meta });
			}
		}
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::info_impl(const details::log_message& log_msg,
		details::format_args_list args)
	{
		this->log(log_msg, level::info, args);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::warning_impl(const details::log_message& log_msg,
		details::format_args_list args)
	{
		log(log_msg, level::warning, args);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::error_impl(const details::log_message& log_msg,
		details::format_args_list args)
	{
		this->log(log_msg, level::error, args);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::critical_impl(const details::log_message& log_msg,
		details::format_args_list args)
	{
		this->log(log_msg, level::critical, args);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::debug_impl(const details::log_message& log_msg,
		details::format_args_list args)
	{
		this->log(log_msg, level::debug, args);
	}
}