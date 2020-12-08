#pragma once

#include "logger.h"
#include "sinks/sink_factory.h"
#include "level.h"
#include "registry.h"

namespace lwlog
{
	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	template<typename... SinkParams>
	logger<StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name, SinkParams&&... params)
		: m_name{ name }
	{
		details::formatter::insert_pattern_data({ {"{logger_name}", "%n", m_name} });
		registry::instance().register_logger(this);

		m_sink_buffer = { sinks::sink_factory<Sinks<ThreadingPolicy>>::request(
			std::forward<SinkParams>(params)...
		)... };
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	template<typename Iterator, typename... SinkParams>
	logger<StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		Iterator begin, Iterator end, SinkParams&&... params)
		: logger{ name, params... }
	{
		m_sink_buffer.insert(m_sink_buffer.end(), begin, end);
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	template<typename... SinkParams>
	logger<StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		primitives::sink_list sink_list, SinkParams&&... params)
		: logger{ name, sink_list.begin(), sink_list.end(), params... }
	{}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	template<typename... SinkParams>
	logger<StoragePolicy, ThreadingPolicy, Sinks...>::logger(std::string_view name,
		primitives::sink_ptr sink, SinkParams&&... params)
		: logger{ name, { std::move(sink) }, params... }
	{}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::add_sink(primitives::sink_ptr sink)
	{
		m_sink_buffer.emplace_back(sink);
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::remove_sink(primitives::sink_ptr sink)
	{
		for (std::size_t i = 0; i < m_sink_buffer.size(); ++i)
		{
			if (m_sink_buffer[i] == sink)
			{
				m_sink_buffer.erase(m_sink_buffer.begin() + i);
			}
		}
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::log(std::string_view message, level t_level)
	{
		details::formatter::insert_pattern_data({
			{"^level_color^", "", level_details::color_value(t_level)},
			{"{message}",		"%v", message.data()},
			{"{log_level}",		"%l", level_details::to_string(t_level)},
			{"{log_level_abr}",	"%L", std::string(1, level_details::to_string(t_level)[0])}
			});

		for (const auto& sink : m_sink_buffer)
		{
			if (sink->should_sink(t_level))
			{
				sink->sink_it(details::formatter::format(sink->pattern()));
			}
		}
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::set_pattern(std::string_view pattern)
	{
		for (const auto& sink : m_sink_buffer)
		{ 
			sink->set_pattern(pattern);
		}
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::add_pattern_attribute(primitives::attribute_t attribute)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink->add_pattern_attribute(attribute);
		}
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::set_level_filter(level t_level)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink->set_level_filter(t_level);
		}
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::info(std::string_view message)
	{
		log(message, level::info);
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::warning(std::string_view message)
	{
		log(message, level::warning);
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::error(std::string_view message)
	{
		log(message, level::error);
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::critical(std::string_view message)
	{
		log(message, level::critical);
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	void logger<StoragePolicy, ThreadingPolicy, Sinks...>::debug(std::string_view message)
	{
		log(message, level::debug);
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	std::string logger<StoragePolicy, ThreadingPolicy, Sinks...>::name() const
	{
		return m_name;
	}

	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy,
		template<typename> typename... Sinks>
	typename logger<StoragePolicy, ThreadingPolicy, Sinks...>::Storage& 
		logger<StoragePolicy, ThreadingPolicy, Sinks...>::sinks()
	{
		return m_sink_buffer;
	}
}