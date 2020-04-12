#include "lwlog.h"

namespace lwlog
{
	LWLOG_API void register_logger(interface::logger_ptr logger)
	{
		return registry::instance().register_logger(logger);
	}

	LWLOG_API void set_automatic_registry(bool automatic)
	{
		return registry::instance().set_automatic_registry(automatic);
	}

	LWLOG_API void drop(std::string_view logger_name)
	{
		return registry::instance().drop(logger_name);
	}

	LWLOG_API void drop_all()
	{
		return registry::instance().drop_all();
	}

	LWLOG_API void apply_to_all(const std::function<void(interface::logger_ptr)>& fn)
	{
		registry::instance().apply_to_all(fn);
	}

	LWLOG_API bool is_registry_automatic()
	{
		return registry::instance().is_registry_automatic();
	}

	LWLOG_API interface::logger_ptr get(std::string_view logger_name)
	{
		return registry::instance().get(logger_name);
	}

	LWLOG_API std::shared_ptr<interface::logger> default_logger()
	{
		return registry::instance().default_logger();
	}

	LWLOG_API void add_pattern_attribute(details::pattern_attribute attribute)
	{
		registry::instance().default_logger()->add_pattern_attribute(attribute);
	}

	LWLOG_API void info(std::string_view message)
	{
		registry::instance().default_logger()->info(message);
	}

	LWLOG_API void warning(std::string_view message)
	{
		registry::instance().default_logger()->warning(message);
	}

	LWLOG_API void error(std::string_view message)
	{
		registry::instance().default_logger()->error(message);
	}

	LWLOG_API void critical(std::string_view message)
	{
		registry::instance().default_logger()->critical(message);
	}

	LWLOG_API void debug(std::string_view message)
	{
		registry::instance().default_logger()->debug(message);
	}

	LWLOG_API void backtrace(std::size_t buffer_size)
	{
		return registry::instance().default_logger()->backtrace(buffer_size);
	}

	LWLOG_API void disable_backtrace()
	{
		return registry::instance().default_logger()->disable_backtrace();
	}

	LWLOG_API void set_backtrace_stamp(std::string_view stamp)
	{
		return registry::instance().default_logger()->set_backtrace_stamp(stamp);
	}

	LWLOG_API void display_backtrace()
	{
		return registry::instance().default_logger()->display_backtrace();
	}

	LWLOG_API void dump_backtrace()
	{
		return registry::instance().default_logger()->dump_backtrace();
	}
}

namespace lwlog::global
{
	LWLOG_API void add_sink(sinks::sink_ptr sink)
	{
		registry::instance().apply_to_all([sink](interface::logger_ptr logger)
			{
				logger->add_sink(sink);
			});
	}

	LWLOG_API void remove_sink(sinks::sink_ptr sink)
	{
		registry::instance().apply_to_all([sink](interface::logger_ptr logger)
			{
				logger->remove_sink(sink);
			});
	}

	LWLOG_API void set_pattern(std::string_view pattern)
	{
		registry::instance().apply_to_all([pattern](interface::logger_ptr logger)
			{
				logger->set_pattern(pattern);
			});
	}

	LWLOG_API void add_pattern_attribute(details::pattern_attribute attribute)
	{
		registry::instance().apply_to_all([attribute](interface::logger_ptr logger)
			{
				logger->add_pattern_attribute(attribute);
			});
	}

	LWLOG_API void set_level_visibility(std::initializer_list<sink_level> level_list)
	{
		registry::instance().apply_to_all([level_list](interface::logger_ptr logger)
			{
				logger->set_level_visibility(level_list);
			});
	}

	LWLOG_API void backtrace(std::size_t buffer_size)
	{
		registry::instance().apply_to_all([buffer_size](interface::logger_ptr logger)
			{
				logger->backtrace(buffer_size);
			});
	}

	LWLOG_API void disable_backtrace()
	{
		registry::instance().apply_to_all([](interface::logger_ptr logger)
			{
				logger->disable_backtrace();
			});
	}

	LWLOG_API void set_backtrace_stamp(std::string_view stamp)
	{
		registry::instance().apply_to_all([stamp](interface::logger_ptr logger)
			{
				logger->set_backtrace_stamp(stamp);
			});
	}

	LWLOG_API void display_backtrace()
	{
		registry::instance().apply_to_all([](interface::logger_ptr logger)
			{
				logger->display_backtrace();
			});
	}

	LWLOG_API void dump_backtrace()
	{
		registry::instance().apply_to_all([](interface::logger_ptr logger)
			{
				logger->dump_backtrace();
			});
	}
}