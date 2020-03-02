#include "logger.h"
#include "sinks/sink_factory.h"
#include "sinks/sink_level.h"
#include "registry.h"
#include "formatter.h"

namespace lwlog
{
	template<typename ... SinkPolicyArgs>
	logger<SinkPolicyArgs...>::logger(std::string_view name)
		: m_name(name)
	{
		if (registry::instance().is_registry_automatic() == true)
		{
			registry::instance().register_logger(this);
		}

		(m_sink_buffer.emplace_back(sink_factory<SinkPolicyArgs>::request()), ...);
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::log(std::string_view message, sink_level level)
	{
		m_message = message;

		formatter::insert_pattern_data({ "%logger_name%",	"%n" }, m_name);
		formatter::insert_pattern_data({ "%message%",		"%v" }, m_message);
		formatter::insert_pattern_data({ "%log_level%",		"%l" }, m_level_string);
		formatter::insert_pattern_data({ "%log_level_abr%",	"%L" }, std::to_string(std::toupper(m_level_string[0])));

		for (const auto& sink : m_sink_buffer)
		{
			if (sink.get()->should_sink(level))
			{
				sink.get()->sink_it(formatter::format(sink.get()->get_pattern()));
				m_tracer.push_in_backtrace_buffer(formatter::format(sink.get()->get_pattern()));
			}
		}
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::set_pattern(std::string_view pattern)
	{
		for (const auto& sink : m_sink_buffer)
		{ 
			sink.get()->set_pattern(pattern);
		}
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::set_level_visibility(std::initializer_list<sink_level> level_list)
	{
		for (const auto& sink : m_sink_buffer)
		{
			sink.get()->set_level_visibility(level_list);
		}
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::info(std::string_view message)
	{
		m_level_string = "info";
		log(message, sink_level::info);
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::warning(std::string_view message)
	{
		m_level_string = "warning";
		log(message, sink_level::warning);
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::error(std::string_view message)
	{
		m_level_string = "error";
		log(message, sink_level::error);
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::critical(std::string_view message)
	{
		m_level_string = "critical";
		log(message, sink_level::critical);
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::debug(std::string_view message)
	{
		m_level_string = "debug";
		log(message, sink_level::debug);
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::backtrace(std::size_t buffer_size)
	{
		m_tracer.backtrace(buffer_size);
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::disable_backtrace()
	{
		m_tracer.disable_backtrace();
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::set_backtrace_stamp(std::string_view stamp)
	{
		m_tracer.set_backtrace_stamp(stamp);
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::display_backtrace()
	{
		m_tracer.display_backtrace();
	}

	template<typename ... SinkPolicyArgs>
	void logger<SinkPolicyArgs...>::delete_backtrace()
	{
		m_tracer.delete_backtrace();
	}

	template<typename ... SinkPolicyArgs>
	inline std::string logger<SinkPolicyArgs...>::name() const
	{
		return m_name;
	}

	template<typename ... SinkPolicyArgs>
	inline std::vector<std::shared_ptr<sinks::sink>> logger<SinkPolicyArgs...>::sinks() const
	{
		return m_sink_buffer;
	}

	template class logger<sinks::console_sink, sinks::file_sink>;
	template class logger<sinks::file_sink, sinks::console_sink>;
	template class logger<sinks::console_sink>;
	template class logger<sinks::file_sink>;
}
