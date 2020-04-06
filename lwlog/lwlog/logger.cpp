#include "logger.h"

namespace lwlog
{
	template<typename ... SinkPolicy>
	logger<SinkPolicy...>::logger(const logger& other)
		: m_name(other.m_name)
		, m_message(other.m_message)
		, m_level_string(other.m_level_string)
		, m_sink_buffer(other.m_sink_buffer)
		, m_tracer(other.m_tracer)
	{}

	template<typename ... SinkPolicy>
	logger<SinkPolicy...>::logger(logger&& other) noexcept
		: m_name(std::move(other.m_name))
		, m_message(std::move(other.m_message))
		, m_level_string(std::move(other.m_level_string))
		, m_sink_buffer(std::move(other.m_sink_buffer))
		, m_tracer(std::move(other.m_tracer))
	{}

	template<typename ... SinkPolicy>
	logger<SinkPolicy...>& logger<SinkPolicy...>::operator=(logger& other)
	{
		if (this == &other) 
		{ 
			return *this;
		}
		m_name.swap(other.m_name);
		m_message.swap(other.m_message);
		m_level_string.swap(other.m_level_string);
		m_sink_buffer.swap(other.m_sink_buffer);
		std::swap(m_tracer, other.m_tracer);
		return *this;
	}

	template<typename ... SinkPolicy>
	logger<SinkPolicy...>& logger<SinkPolicy...>::operator=(logger&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}
		m_name = std::move(other.m_name);
		m_message = std::move(other.m_message);
		m_level_string = std::move(other.m_level_string);
		m_sink_buffer = std::move(other.m_sink_buffer);
		m_tracer = std::move(other.m_tracer);
		return *this;
	}

	template<typename ...SinkPolicy>
	void logger<SinkPolicy...>::add_sink(sinks::sink_ptr sink)
	{
		m_sink_buffer.emplace_back(sink);
	}

	template<typename ...SinkPolicy>
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
		m_message = message;

		details::formatter::insert_pattern_data({ 
			{"{logger_name}",	"%n", m_name},
			{"{message}",		"%v", m_message},
			{"{log_level}",		"%l", m_level_string},
			{"{log_level_abr}",	"%L", std::string(1, std::toupper(m_level_string[0]))} 
			});

		for (const auto& sink : m_sink_buffer)
		{
			if (sink->should_sink(level))
			{
				sink->sink_it(details::formatter::format(sink->get_pattern(), sink->should_color()));
				m_tracer.push_in_buffer(details::formatter::format(sink->get_pattern(), sink->should_color()));
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

	template<typename ...SinkPolicy>
	void logger<SinkPolicy...>::add_pattern_attribute(details::pattern_attribute attribute)
	{
		details::formatter::insert_pattern_data({ {attribute.verbose, attribute.shortened, attribute.attribute } });
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::set_level_visibility(std::initializer_list<sink_level> level_list)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink->set_level_visibility(level_list);
		}
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::info(std::string_view message)
	{
		m_level_string = "info";
		log(message, sink_level::info);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::warning(std::string_view message)
	{
		m_level_string = "warning";
		log(message, sink_level::warning);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::error(std::string_view message)
	{
		m_level_string = "error";
		log(message, sink_level::error);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::critical(std::string_view message)
	{
		m_level_string = "critical";
		log(message, sink_level::critical);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::debug(std::string_view message)
	{
		m_level_string = "debug";
		log(message, sink_level::debug);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::backtrace(std::size_t buffer_size)
	{
		m_tracer.backtrace(buffer_size);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::disable_backtrace()
	{
		m_tracer.disable();
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::set_backtrace_stamp(std::string_view stamp)
	{
		m_tracer.set_stamp(stamp);
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::display_backtrace()
	{
		m_tracer.display();
	}

	template<typename ... SinkPolicy>
	void logger<SinkPolicy...>::dump_backtrace()
	{
		m_tracer.dump();
	}

	template<typename ... SinkPolicy>
	inline std::string logger<SinkPolicy...>::name() const
	{
		return m_name;
	}

	template<typename ... SinkPolicy>
	inline std::vector<sinks::sink_ptr> logger<SinkPolicy...>::sinks() const
	{
		return m_sink_buffer;
	}

	template class logger<>;
	template class logger<sinks::console_sink>;
	template class logger<sinks::file_sink>;
	template class logger<sinks::console_sink, sinks::file_sink>;
	template class logger<sinks::file_sink, sinks::console_sink>;
}
