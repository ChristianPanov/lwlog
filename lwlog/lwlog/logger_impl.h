#pragma once

#include "logger.h"
#include "sinks/sink_factory.h"
#include "registry.h"

namespace lwlog
{
	template<typename ... SinkPolicy>
	template<typename ... SinkParams>
	logger<SinkPolicy...>::logger(std::string_view name, SinkParams&& ... params)
		: m_name(name)
	{
		if (registry::instance().is_registry_automatic() && !name.empty())
		{
			registry::instance().register_logger(this);
		}

		(m_sink_buffer.emplace_back(
			sinks::sink_factory<SinkPolicy>::request(std::forward<SinkParams>(params)...)
		), ...);
	}

	template<typename ... SinkPolicy>
	template<typename Iterator, typename ... SinkParams>
	logger<SinkPolicy...>::logger(std::string_view name, 
		Iterator begin, Iterator end, SinkParams&& ... params)
		: logger(name, params...)
	{
		m_sink_buffer.insert(m_sink_buffer.end(), begin, end);
	}

	template<typename ... SinkPolicy>
	template<typename ... SinkParams>
	logger<SinkPolicy...>::logger(std::string_view name, 
		sinks::sink_list sink_list, SinkParams&& ... params)
		: logger<SinkPolicy...>(name, sink_list.begin(), sink_list.end(), params...)
	{}

	template<typename ... SinkPolicy>
	template<typename ... SinkParams>
	logger<SinkPolicy...>::logger(std::string_view name, 
		sinks::sink_ptr sink, SinkParams&& ... params)
		: logger<SinkPolicy...>(name, { std::move(sink) }, params...)
	{}
}