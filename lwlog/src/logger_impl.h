#pragma once

#include "logger.h"
#include "sinks/sink_factory.h"
#include "registry.h"

namespace lwlog
{
	template<typename LogPolicy, typename FlushPolicy, 
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	template<typename... SinkParams>
	logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name, SinkParams&&... params)
		: m_name{ name }
	{
		LogPolicy::init(m_backend);

		if(registry::instance().is_registry_automatic()) 
			registry::instance().register_logger(this);

		m_backend.sink_storage = { sinks::sink_factory<Sinks<FlushPolicy, ThreadingPolicy>>::request(
			std::forward<SinkParams>(params)...
		)... };

		this->add_attribute("{name}", m_name);
		this->add_attribute("%n", m_name);
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	template<typename Iterator, typename... SinkParams>
	logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name, 
		Iterator begin, Iterator end, SinkParams&&... params)
		: logger{ name, params... }
	{
		m_backend.sink_storage.insert(m_backend.sink_storage.end(), begin, end);
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	template<typename... SinkParams>
	logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		sink_list sink_list, SinkParams&&... params)
		: logger{ name, sink_list.begin(), sink_list.end(), params... }
	{}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	template<typename... SinkParams>
	logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name, 
		sink_ptr sink, SinkParams&&... params)
		: logger{ name, { sink }, params... }
	{}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::add_sink(sink_ptr sink)
	{
		m_backend.sink_storage.push_back(sink);
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::remove_sink(sink_ptr sink)
	{
		for (std::size_t i = 0; i < m_backend.sink_storage.size(); ++i)
		{
			if (m_backend.sink_storage[i] == sink) storage.erase(m_backend.sink_storage.begin() + i);
		}
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::set_pattern(std::string_view pattern)
	{
		for (const auto& sink : m_backend.sink_storage)
		{ 
			sink->set_pattern(pattern);
		}
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::add_attribute(std::string_view flag,
		details::attrib_value value)
	{
		for (const auto& sink : m_backend.sink_storage)
		{
			sink->add_attribute(flag, value);
		}
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::add_attribute(std::string_view flag,
		details::attrib_value value, details::attrib_callback_t fn)
	{
		for (const auto& sink : m_backend.sink_storage)
		{
			sink->add_attribute(flag, value, fn);
		}
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::set_level_filter(level t_level)
	{
		for (const auto& sink : m_backend.sink_storage)
		{
			sink->set_level_filter(t_level);
		}
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	std::string_view logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::name() const
	{
		return m_name;
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	std::vector<sink_ptr>& logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::sinks()
	{
		return m_backend.sink_storage;
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::log(const details::log_message& log_msg, 
		level t_level, details::format_args_list args)
	{
		LogPolicy::log(m_backend, { LWLOG_FORMAT_FN(log_msg.message, args), t_level, log_msg.meta });
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::info_impl(const details::log_message& log_msg, 
		details::format_args_list args)
	{
		this->log(log_msg, level::info, args);
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::warning_impl(const details::log_message& log_msg, 
		details::format_args_list args)
	{
		this->log(log_msg, level::warning, args);
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::error_impl(const details::log_message& log_msg, 
		details::format_args_list args)
	{
		this->log(log_msg, level::error, args);
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::critical_impl(const details::log_message& log_msg, 
		details::format_args_list args)
	{
		this->log(log_msg, level::critical, args);
	}

	template<typename LogPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	void logger<LogPolicy, FlushPolicy, ThreadingPolicy, Sinks...>::debug_impl(const details::log_message& log_msg, 
		details::format_args_list args)
	{
		this->log(log_msg, level::debug, args);
	}
}