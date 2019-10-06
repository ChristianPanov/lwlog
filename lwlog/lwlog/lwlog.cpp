#include "lwlog.h"
#include "log_level.h"
#include "formatter.h"
#include "registry.h"
#include "print.h"
#include "details/backtracer.h"

namespace lwlog
{
	template<typename SinkPolicy>
	logger<SinkPolicy>::logger(std::string_view logger_name)
		: m_logger_name(logger_name)
		, m_sink(sink_factory<SinkPolicy>::request())
	{}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::backtrace(std::size_t buffer_size)
	{
		m_tracer.backtrace(buffer_size);
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::set_backtrace_stamp(std::string_view stamp)
	{
		m_tracer.set_backtrace_stamp(stamp);
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::display_backtrace()
	{
		m_tracer.display_backtrace();
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::delete_backtrace()
	{
		m_tracer.delete_backtrace();
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::push_in_backtrace_buffer(std::string_view message)
	{
		m_tracer.push_in_backtrace_buffer(message);
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::log(std::string_view message, level log_level)
	{
		m_message = message;

		formatter::insert_pattern_data({"%logger_name%",	"%n"}, m_logger_name);
		formatter::insert_pattern_data({"%message%",		"%v"}, m_message);
		formatter::insert_pattern_data({"%log_level%",		"%l"}, m_level_string);
		formatter::insert_pattern_data({"%log_level_abr%",	"%L"}, std::string(1, toupper(m_level_string[0])));

		m_sink.get()->sink_it(formatter::format(m_pattern), log_level);

		m_tracer.push_in_backtrace_buffer(formatter::format(m_pattern));
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::info(std::string_view message)
	{
		m_level_string = "info";
		log(message, level::info);
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::warning(std::string_view message)
	{
		m_level_string = "warning";
		log(message, level::warning);
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::error(std::string_view message)
	{
		m_level_string = "error";
		log(message, level::error);
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::critical(std::string_view message)
	{
		m_level_string = "critical";
		log(message, level::critical);
	}

	template<typename SinkPolicy>
	void logger<SinkPolicy>::debug(std::string_view message)
	{
		m_level_string = "debug";
		log(message, level::debug);
	}

	template<typename SinkPolicy>
	inline std::string logger<SinkPolicy>::get_name() const
	{
		return m_logger_name;
	}

	template class logger<sinks::console_sink>;
	template class logger<sinks::file_sink>;
}
