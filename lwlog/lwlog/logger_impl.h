#pragma once

#include "logger.h"
#include "sinks/sink_factory.h"
#include "registry.h"

namespace lwlog
{
	template<typename ... SinkPolicy>
	template<typename ... SinkParams>
	logger<SinkPolicy...>::logger(std::string_view name, SinkParams&&... params)
		: m_name{ name }
	{
		details::formatter::insert_pattern_data({ {"{logger_name}", "%n", m_name} });
		registry::instance().register_logger(this);
		(m_sink_buffer.emplace_back(
			sinks::sink_factory<SinkPolicy>::request(std::forward<SinkParams>(params)...)
		), ...);
	}

	template<typename ... SinkPolicy>
	template<typename Iterator, typename ... SinkParams>
	logger<SinkPolicy...>::logger(std::string_view name, 
		Iterator begin, Iterator end, SinkParams&&... params)
		: logger{ name, params... }
	{
		m_sink_buffer.insert(m_sink_buffer.end(), begin, end);
	}

	template<typename ... SinkPolicy>
	template<typename ... SinkParams>
	logger<SinkPolicy...>::logger(std::string_view name, 
		sinks::sink_list sink_list, SinkParams&&... params)
		: logger<SinkPolicy...>{ name, sink_list.begin(), sink_list.end(), params... }
	{}

	template<typename ... SinkPolicy>
	template<typename ... SinkParams>
	logger<SinkPolicy...>::logger(std::string_view name, 
		sinks::sink_ptr sink, SinkParams&&... params)
		: logger<SinkPolicy...>{ name, { std::move(sink) }, params... }
	{}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::add_sink(sinks::sink_ptr sink)
	{
		m_sink_buffer.emplace_back(sink);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::remove_sink(sinks::sink_ptr sink)
	{
		for (int i = 0; i < m_sink_buffer.size(); ++i)
		{
			if (m_sink_buffer[i] == sink)
			{
				m_sink_buffer.erase(m_sink_buffer.begin() + i);
			}
		}
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::log(std::string_view message, sink_level level)
	{
		for (const auto& sink : m_sink_buffer)
		{
			if (sink->should_sink(level))
			{
				m_message = { {
					message.data(),
					sink->get_pattern(),
					level,
					sink->should_color()
				} };

				sink->sink_it(m_message.message());
			}
		}
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::set_pattern(std::string_view pattern)
	{
		for (const auto& sink : m_sink_buffer)
		{ 
			sink->set_pattern(pattern);
		}
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::add_pattern_attribute(details::pattern_attribute attribute)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink->add_pattern_attribute(attribute);
		}
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::set_level_filter(std::initializer_list<sink_level> level_list)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink->set_level_filter(level_list);
		}
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::info(std::string_view message)
	{
		log(message, sink_level::info);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::warning(std::string_view message)
	{
		log(message, sink_level::warning);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::error(std::string_view message)
	{
		log(message, sink_level::error);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::critical(std::string_view message)
	{
		log(message, sink_level::critical);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::debug(std::string_view message)
	{
		log(message, sink_level::debug);
	}

	template<typename ... SinkPolicy>
	std::string logger<SinkPolicy...>::name() const
	{
		return m_name;
	}

	template<typename ... SinkPolicy>
	std::vector<sinks::sink_ptr>& logger<SinkPolicy...>::sinks()
	{
		return m_sink_buffer;
	}
}