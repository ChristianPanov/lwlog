#pragma once

#include "sinks/sink_factory.h"

namespace lwlog
{
	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename... SinkParams>
	logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::logger(
		std::string_view name, SinkParams&&... params)
		: m_name{ name }
	{
		LogExecutionPolicy::template init<BufferLimits>(m_backend);

		m_backend.sink_storage = { sinks::sink_factory<BufferLimits, 
			Sinks<BufferLimits, FlushPolicy, ThreadingPolicy>>::request(std::forward<SinkParams>(params)...)... 
		};

		logger::add_attribute("{name}", m_name);
		logger::add_attribute("%n", m_name);

		logger::set_topic_separator("/");
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename Iterator, typename... SinkParams>
	logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::logger(
		std::string_view name, Iterator begin, Iterator end, SinkParams&&... params)
		: logger{ name, params... }
	{
		m_backend.sink_storage.insert(m_backend.sink_storage.end(), begin, end);
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename... SinkParams>
	logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::logger(
		std::string_view name, sink_list<BufferLimits> sink_list, SinkParams&&... params)
		: logger{ name, sink_list.begin(), sink_list.end(), params... }
	{}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename... SinkParams>
	logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::logger(
		std::string_view name, sink_ptr<BufferLimits> sink, SinkParams&&... params)
		: logger{ name, { sink }, params... }
	{}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::add_sink(
		sink_ptr<BufferLimits> sink)
	{
		m_backend.sink_storage.push_back(sink);
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::remove_sink(
		sink_ptr<BufferLimits> sink)
	{
		for (std::size_t i = 0; i < m_backend.sink_storage.size(); ++i)
		{
			if (m_backend.sink_storage[i] == sink)
			{
				m_backend.sink_storage.erase(m_backend.sink_storage.begin() + i);
			}
		}
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::set_level_filter(level log_level)
	{
		for (const auto& sink : m_backend.sink_storage)
		{
			sink->set_level_filter(log_level);
		}
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::set_pattern(
		std::string_view pattern)
	{
		for (const auto& sink : m_backend.sink_storage)
		{ 
			sink->set_pattern(pattern);
		}
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::add_attribute(
		std::string_view flag, details::attrib_value value)
	{
		for (const auto& sink : m_backend.sink_storage)
		{
			sink->add_attribute(flag, value);
		}
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::add_attribute(
		std::string_view flag, details::attrib_value value, const details::attrib_callback_t& fn)
	{
		for (const auto& sink : m_backend.sink_storage)
		{
			sink->add_attribute(flag, value, fn);
		}
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::set_topic_separator(
		const char* separator)
	{
		m_backend.topics.set_separator(separator);
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::start_topic(
		const char* topic)
	{
		m_backend.topics.start_topic(topic);
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::end_topic()
	{
		m_backend.topics.end_topic();
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	std::string_view logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::name() const
	{
		return m_name;
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	std::vector<sink_ptr<BufferLimits>>& logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::sinks()
	{
		return m_backend.sink_storage;
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename... Args>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::log(
		const details::log_message& log_msg, level log_level, Args&&... args)
	{
		LogExecutionPolicy::template log<BufferLimits>(m_backend, log_msg.message, 
			log_level, log_msg.meta, std::forward<Args>(args)...);
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename... Args>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::info(
		const details::log_message& log_msg, Args&&... args)
	{
		this->log(log_msg, level::info, std::forward<Args>(args)...);
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename... Args>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::warning(
		const details::log_message& log_msg, Args&&... args)
	{
		this->log(log_msg, level::warning, std::forward<Args>(args)...);
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename... Args>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::error(
		const details::log_message& log_msg, Args&&... args)
	{
		this->log(log_msg, level::error, std::forward<Args>(args)...);
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename... Args>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::critical(
		const details::log_message& log_msg, Args&&... args)
	{
		this->log(log_msg, level::critical, std::forward<Args>(args)...);
	}

	template<typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename> typename... Sinks>
	template<typename... Args>
	void logger<BufferLimits, LogExecutionPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::debug(
		const details::log_message& log_msg, Args&&... args)
	{
		this->log(log_msg, level::debug, std::forward<Args>(args)...);
	}
}