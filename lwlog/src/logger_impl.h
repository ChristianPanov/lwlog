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
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::log(std::string_view message, level t_level, 
		details::source_meta meta)
	{
		for (const auto& sink : m_sink_storage)
		{
			if (sink->should_sink(t_level))
			{
				LogPolicy::log(sink, details::record{ message, t_level, meta });
			}
		}
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
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::info(std::string_view message, 
		details::source_meta meta)
	{
		this->log(message, level::info, meta);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::warning(std::string_view message, 
		details::source_meta meta)
	{
		this->log(message, level::warning, meta);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::error(std::string_view message, 
		details::source_meta meta)
	{
		this->log(message, level::error, meta);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::critical(std::string_view message, 
		details::source_meta meta)
	{
		this->log(message, level::critical, meta);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::debug(std::string_view message, 
		details::source_meta meta)
	{
		this->log(message, level::debug, meta);
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
}