#include "logger.h"
#include "log_level.h"
#include "formatter.h"

namespace lwlog
{
	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	logger<SinkPolicy, SinkPolicyArgs...>::logger(std::string_view logger_name)
		: m_logger_name(logger_name)
	{
		m_sink_buffer.emplace_back(sink_factory<SinkPolicy>::request());
		(m_sink_buffer.emplace_back(sink_factory<SinkPolicyArgs>::request()), ...);
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::log(std::string_view message, level log_level)
	{
		m_message = message;

		formatter::insert_pattern_data({ "%logger_name%",	"%n" }, m_logger_name);
		formatter::insert_pattern_data({ "%message%",		"%v" }, m_message);
		formatter::insert_pattern_data({ "%log_level%",		"%l" }, m_level_string);
		formatter::insert_pattern_data({ "%log_level_abr%",	"%L" }, std::to_string(std::toupper(m_level_string[0])));

		for (const auto& sink : m_sink_buffer)
		{
			sink.get()->sink_it(formatter::format(sink.get()->get_pattern()));
			m_tracer.push_in_backtrace_buffer(formatter::format(sink.get()->get_pattern()));
		}
	}

	template<typename SinkPolicy, typename ...SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::set_pattern(std::string_view pattern)
	{
		for (const auto& sink : m_sink_buffer)
		{ 
			sink.get()->set_pattern(pattern);
		}
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::info(std::string_view message)
	{
		m_level_string = "info";
		log(message, level::info);
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::warning(std::string_view message)
	{
		m_level_string = "warning";
		log(message, level::warning);
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::error(std::string_view message)
	{
		m_level_string = "error";
		log(message, level::error);
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::critical(std::string_view message)
	{
		m_level_string = "critical";
		log(message, level::critical);
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::debug(std::string_view message)
	{
		m_level_string = "debug";
		log(message, level::debug);
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::backtrace(std::size_t buffer_size)
	{
		m_tracer.backtrace(buffer_size);
	}

	template<typename SinkPolicy, typename ...SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::disable_backtrace()
	{
		m_tracer.disable_backtrace();
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::set_backtrace_stamp(std::string_view stamp)
	{
		m_tracer.set_backtrace_stamp(stamp);
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::display_backtrace()
	{
		m_tracer.display_backtrace();
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	void logger<SinkPolicy, SinkPolicyArgs...>::delete_backtrace()
	{
		m_tracer.delete_backtrace();
	}

	template<typename SinkPolicy, typename ... SinkPolicyArgs>
	inline std::string logger<SinkPolicy, SinkPolicyArgs...>::get_name() const
	{
		return m_logger_name;
	}

	template class logger<sinks::console_sink, sinks::file_sink>;
	template class logger<sinks::file_sink, sinks::console_sink>;
	template class logger<sinks::console_sink>;
	template class logger<sinks::file_sink>;
}
