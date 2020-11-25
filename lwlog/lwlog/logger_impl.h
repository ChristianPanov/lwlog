#pragma once

#include "logger.h"
#include "sinks/sink_factory.h"
#include "sinks/sink_level.h"
#include "registry.h"

namespace lwlog
{
	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	template<typename ... SinkParams>
	logger<StoragePolicy, Sinks...>::logger(std::string_view name, SinkParams&&... params)
		: m_name{ name }
	{
		details::formatter::insert_pattern_data({ {"{logger_name}", "%n", m_name} });
		registry::instance().register_logger(this);

		m_sink_buffer = { sinks::sink_factory<Sinks>::request(
			std::forward<SinkParams>(params)...
		)... };
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	template<typename Iterator, typename ... SinkParams>
	logger<StoragePolicy, Sinks...>::logger(std::string_view name,
		Iterator begin, Iterator end, SinkParams&&... params)
		: logger{ name, params... }
	{
		m_sink_buffer.insert(m_sink_buffer.end(), begin, end);
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	template<typename ... SinkParams>
	logger<StoragePolicy, Sinks...>::logger(std::string_view name,
		primitives::sink_list sink_list, SinkParams&&... params)
		: logger<Sinks...>{ name, sink_list.begin(), sink_list.end(), params... }
	{}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	template<typename ... SinkParams>
	logger<StoragePolicy, Sinks...>::logger(std::string_view name,
		primitives::sink_ptr sink, SinkParams&&... params)
		: logger<Sinks...>{ name, { std::move(sink) }, params... }
	{}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::add_sink(primitives::sink_ptr sink)
	{
		m_sink_buffer.emplace_back(sink);
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::remove_sink(primitives::sink_ptr sink)
	{
		for (std::size_t i = 0; i < m_sink_buffer.size(); ++i)
		{
			if (m_sink_buffer[i] == sink)
			{
				m_sink_buffer.erase(m_sink_buffer.begin() + i);
			}
		}
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::log(std::string_view message, sink_level level)
	{
		for (const auto& sink : m_sink_buffer)
		{
			if (sink->should_sink(level))
			{
				m_message = { {
					message.data(),
					sink->pattern(),
					level,
					sink->should_color()
				} };

				sink->sink_it(m_message.message());
			}
		}
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::set_pattern(std::string_view pattern)
	{
		for (const auto& sink : m_sink_buffer)
		{ 
			sink->set_pattern(pattern);
		}
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::add_pattern_attribute(primitives::attribute_t attribute)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink->add_pattern_attribute(attribute);
		}
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::set_level_filter(std::initializer_list<sink_level> level_list)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink->set_level_filter(level_list);
		}
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::info(std::string_view message)
	{
		log(message, sink_level::info);
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::warning(std::string_view message)
	{
		log(message, sink_level::warning);
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::error(std::string_view message)
	{
		log(message, sink_level::error);
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::critical(std::string_view message)
	{
		log(message, sink_level::critical);
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	void logger<StoragePolicy, Sinks...>::debug(std::string_view message)
	{
		log(message, sink_level::debug);
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	std::string logger<StoragePolicy, Sinks...>::name() const
	{
		return m_name;
	}

	template<template<typename ... Args> typename StoragePolicy, typename ... Sinks>
	std::vector<primitives::sink_ptr>& logger<StoragePolicy, Sinks...>::sinks()
	{
		//return m_sink_buffer;
		return std::vector<primitives::sink_ptr>{};
	}
}