#include "lwlog.h"

#include "sinks/sink.h"
#include "sinks/console_sink.h"
#include "sinks/file_sink.h"
#include "registry.h"

namespace lwlog 
{
	LWLOG_API logger_interface* get(std::string_view logger_name)
	{
		return registry::instance().get(logger_name);
	}

	LWLOG_API std::shared_ptr<logger_interface> default_logger()
	{
		return registry::default_logger();
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
		return registry::default_logger()->delete_backtrace();
	}

	LWLOG_API void apply_to_all(const std::function<void(logger_interface*)>& fn)
	{
		registry::apply_to_all(fn);
	}

	LWLOG_API void global_set_pattern(std::string_view pattern)
	{
		registry::apply_to_all([pattern](logger_interface* logger)
		{ 
			logger->set_pattern(pattern);
		});
	}

	LWLOG_API void global_set_level_visibility(std::initializer_list<sink_level> level_list)
	{
		registry::apply_to_all([level_list](logger_interface* logger)
		{
			logger->set_level_visibility(level_list);
		});
	}

	LWLOG_API void global_backtrace(std::size_t buffer_size)
	{
		registry::apply_to_all([buffer_size](logger_interface* logger)
		{
			logger->backtrace(buffer_size);
		});
	}

	LWLOG_API void global_disable_backtrace()
	{
		registry::apply_to_all([](logger_interface* logger)
		{
			logger->disable_backtrace();
		});
	}

	LWLOG_API void global_set_backtrace_stamp(std::string_view stamp)
	{
		registry::apply_to_all([stamp](logger_interface* logger)
		{
			logger->set_backtrace_stamp(stamp);
		});
	}

	LWLOG_API void global_display_backtrace()
	{
		registry::apply_to_all([](logger_interface* logger)
		{
			logger->display_backtrace();
		});
	}

	LWLOG_API void global_delete_backtrace()
	{
		registry::apply_to_all([](logger_interface* logger)
		{
			logger->delete_backtrace();
		});
	}
}
