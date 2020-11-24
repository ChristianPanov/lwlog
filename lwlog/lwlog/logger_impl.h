#pragma once

#include "logger.h"
#include "sinks/sink_factory.h"
#include "sinks/sink_level.h"
#include "registry.h"

namespace lwlog
{
	template<typename ... Sinks>
	template<typename ... SinkParams>
	logger<Sinks...>::logger(std::string_view name, SinkParams&&... params)
		: m_name{ name }
	{
		details::formatter::insert_pattern_data({ {"{logger_name}", "%n", m_name} });
		registry::instance().register_logger(this);

		(m_sink_buffer.push_back(
			sinks::sink_factory<Sinks>::request(std::forward<SinkParams>(params)...)
		), ...);
	}

	template<typename ... Sinks>
	template<typename Iterator, typename ... SinkParams>
	logger<Sinks...>::logger(std::string_view name,
		Iterator begin, Iterator end, SinkParams&&... params)
		: logger{ name, params... }
	{
		m_sink_buffer.insert(m_sink_buffer.end(), begin, end);
	}

	template<typename ... Sinks>
	template<typename ... SinkParams>
	logger<Sinks...>::logger(std::string_view name,
		primitives::sink_list sink_list, SinkParams&&... params)
		: logger<Sinks...>{ name, sink_list.begin(), sink_list.end(), params... }
	{}

	template<typename ... Sinks>
	template<typename ... SinkParams>
	logger<Sinks...>::logger(std::string_view name,
		primitives::sink_ptr sink, SinkParams&&... params)
		: logger<Sinks...>{ name, { std::move(sink) }, params... }
	{}

	template<typename ... Sinks>
	void logger<Sinks...>::add_sink(primitives::sink_ptr sink)
	{
		m_sink_buffer.emplace_back(sink);
	}

	template<typename ... Sinks>
	void logger<Sinks...>::remove_sink(primitives::sink_ptr sink)
	{
		for (std::size_t i = 0; i < m_sink_buffer.size(); ++i)
		{
			if (m_sink_buffer[i] == sink)
			{
				m_sink_buffer.erase(m_sink_buffer.begin() + i);
			}
		}
	}

	template<typename ... Sinks>
	void logger<Sinks...>::log(std::string_view message, sink_level level)
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

	template<typename ... Sinks>
	void logger<Sinks...>::set_pattern(std::string_view pattern)
	{
		for (const auto& sink : m_sink_buffer)
		{ 
			sink->set_pattern(pattern);
		}
	}

	template<typename ... Sinks>
	void logger<Sinks...>::add_pattern_attribute(primitives::attribute_t attribute)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink->add_pattern_attribute(attribute);
		}
	}

	template<typename ... Sinks>
	void logger<Sinks...>::set_level_filter(std::initializer_list<sink_level> level_list)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink->set_level_filter(level_list);
		}
	}

	template<typename ... Sinks>
	void logger<Sinks...>::info(std::string_view message)
	{
		log(message, sink_level::info);
	}

	template<typename ... Sinks>
	void logger<Sinks...>::warning(std::string_view message)
	{
		log(message, sink_level::warning);
	}

	template<typename ... Sinks>
	void logger<Sinks...>::error(std::string_view message)
	{
		log(message, sink_level::error);
	}

	template<typename ... Sinks>
	void logger<Sinks...>::critical(std::string_view message)
	{
		log(message, sink_level::critical);
	}

	template<typename ... Sinks>
	void logger<Sinks...>::debug(std::string_view message)
	{
		log(message, sink_level::debug);
	}

	template<typename ... Sinks>
	std::string logger<Sinks...>::name() const
	{
		return m_name;
	}

	template<typename ... Sinks>
	std::vector<primitives::sink_ptr>& logger<Sinks...>::sinks()
	{
		return m_sink_buffer;
	}
}