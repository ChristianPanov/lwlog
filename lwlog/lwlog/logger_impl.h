#pragma once

#include "logger.h"
#include "sinks/sink_factory.h"
#include "level.h"
#include "registry.h"

namespace lwlog
{
	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	template<typename... SinkParams>
	logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name, SinkParams&&... params)
		: m_name{ name }
	{
		registry::instance().register_logger(this);

		m_sink_storage = { sinks::sink_factory<Sinks<ThreadingPolicy>>::request(
			std::forward<SinkParams>(params)...
		)... };
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	template<typename Iterator, typename... SinkParams>
	logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		Iterator begin, Iterator end, SinkParams&&... params)
		: logger{ name, params... }
	{
		m_sink_storage.insert(m_sink_buffer.end(), begin, end);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	template<typename... SinkParams>
	logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		primitives::sink_list sink_list, SinkParams&&... params)
		: logger{ name, sink_list.begin(), sink_list.end(), params... }
	{}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	template<typename... SinkParams>
	logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		primitives::sink_ptr sink, SinkParams&&... params)
		: logger{ name, { sink }, params... }
	{}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::add_sink(primitives::sink_ptr sink)
	{
		m_sink_storage.push_back(sink);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::remove_sink(primitives::sink_ptr sink)
	{
		for (std::size_t i = 0; i < m_sink_storage.size(); ++i)
		{
			if (m_sink_storage[i] == sink)
			{
				m_sink_storage.erase(m_sink_storage.begin() + i);
			}
		}
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::sink_logs()
	{
		LogPolicy::sink_logs();
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::log(std::string_view message, level t_level)
	{
		for (const auto& sink : m_sink_storage)
		{
			if (sink->should_sink(t_level))
			{
				LogPolicy::log(sink,
					details::log_message{ sink->pattern().data(), message.data(), m_name.data(), t_level }
				);
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
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::set_level_filter(level t_level)
	{
		for (const auto& sink : m_sink_storage)
		{
			sink->set_level_filter(t_level);
		}
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::info(std::string_view message)
	{
		log(message, level::info);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::warning(std::string_view message)
	{
		log(message, level::warning);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::error(std::string_view message)
	{
		log(message, level::error);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::critical(std::string_view message)
	{
		log(message, level::critical);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	void logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::debug(std::string_view message)
	{
		log(message, level::debug);
	}

	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	std::string logger<LogPolicy, StoragePolicy, ThreadingPolicy, Sinks...>::name() const
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