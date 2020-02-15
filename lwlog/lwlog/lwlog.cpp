#include "lwlog.h"

#include "sinks/sink.h"
#include "sinks/console_sink.h"
#include "sinks/file_sink.h"
#include "registry.h"

namespace lwlog 
{
	LWLOG_API void set_pattern(std::string_view pattern)
	{
		registry::instance().default_logger()->set_pattern(pattern);
	}

	LWLOG_API void set_level_visibility(std::initializer_list<sink_level> level_list)
	{
		registry::instance().default_logger()->set_level_visibility(level_list);
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
}
