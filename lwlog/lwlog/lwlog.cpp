#include "lwlog.h"

namespace lwlog 
{
	LWLOG_API interface::logger* get(std::string_view logger_name)
	{
		return registry::instance().get(logger_name);
	}

	LWLOG_API std::shared_ptr<interface::logger> default_logger()
	{
		return registry::default_logger();
	}

	LWLOG_API void add_pattern_attribute(details::pattern_attribute attribute)
	{
		registry::default_logger()->add_pattern_attribute(attribute);
	}

	LWLOG_API void info(std::string_view message)
	{
		registry::default_logger()->info(message);
	}

	LWLOG_API void warning(std::string_view message)
	{
		registry::default_logger()->warning(message);
	}

	LWLOG_API void error(std::string_view message)
	{
		registry::default_logger()->error(message);
	}

	LWLOG_API void critical(std::string_view message)
	{
		registry::default_logger()->critical(message);
	}

	LWLOG_API void debug(std::string_view message)
	{
		registry::default_logger()->debug(message);
	}

	LWLOG_API void backtrace(std::size_t buffer_size)
	{
		return registry::default_logger()->backtrace(buffer_size);
	}

	LWLOG_API void disable_backtrace()
	{
		return registry::default_logger()->disable_backtrace();
	}

	LWLOG_API void set_backtrace_stamp(std::string_view stamp)
	{
		return registry::default_logger()->set_backtrace_stamp(stamp);
	}

	LWLOG_API void display_backtrace()
	{
		return registry::default_logger()->display_backtrace();
	}

	LWLOG_API void delete_backtrace()
	{
		return registry::default_logger()->dump_backtrace();
	}

	LWLOG_API void apply_to_all(const std::function<void(interface::logger*)>& fn)
	{
		registry::apply_to_all(fn);
	}
}

namespace lwlog::global
{
	LWLOG_API void add_sink(sinks::sink_ptr sink)
	{
		registry::apply_to_all([sink](interface::logger* logger)
			{
				logger->add_sink(sink);
			});
	}

	LWLOG_API void remove_sink(sinks::sink_ptr sink)
	{
		registry::apply_to_all([sink](interface::logger* logger)
			{
				logger->remove_sink(sink);
			});
	}

	LWLOG_API void set_pattern(std::string_view pattern)
	{
		registry::apply_to_all([pattern](interface::logger* logger)
			{
				logger->set_pattern(pattern);
			});
	}

	LWLOG_API void add_pattern_attribute(details::pattern_attribute attribute)
	{
		registry::apply_to_all([attribute](interface::logger* logger)
			{
				logger->add_pattern_attribute(attribute);
			});
	}

	LWLOG_API void set_level_visibility(std::initializer_list<sink_level> level_list)
	{
		registry::apply_to_all([level_list](interface::logger* logger)
			{
				logger->set_level_visibility(level_list);
			});
	}

	LWLOG_API void backtrace(std::size_t buffer_size)
	{
		registry::apply_to_all([buffer_size](interface::logger* logger)
			{
				logger->backtrace(buffer_size);
			});
	}

	LWLOG_API void disable_backtrace()
	{
		registry::apply_to_all([](interface::logger* logger)
			{
				logger->disable_backtrace();
			});
	}

	LWLOG_API void set_backtrace_stamp(std::string_view stamp)
	{
		registry::apply_to_all([stamp](interface::logger* logger)
			{
				logger->set_backtrace_stamp(stamp);
			});
	}

	LWLOG_API void display_backtrace()
	{
		registry::apply_to_all([](interface::logger* logger)
			{
				logger->display_backtrace();
			});
	}

	LWLOG_API void delete_backtrace()
	{
		registry::apply_to_all([](interface::logger* logger)
			{
				logger->dump_backtrace();
			});
	}
}