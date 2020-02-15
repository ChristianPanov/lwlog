#pragma once

#include "core.h"
#include "logger.h"

namespace lwlog
{
	using console_logger = logger<sinks::console_sink>;
	using file_logger = logger<sinks::file_sink>;

	/*-------------------------------------------*/
	using console_logger_st = nullptr_t;
	using console_logger_mt = nullptr_t;

	using file_logger_st = nullptr_t;
	using file_logger_mt = nullptr_t;
	/*-------------------------------------------*/

	LWLOG_API void set_pattern(std::string_view pattern);
	LWLOG_API void set_level_visibility(std::initializer_list<sink_level> level_list);

	LWLOG_API void info(std::string_view message);
	LWLOG_API void warning(std::string_view message);
	LWLOG_API void error(std::string_view message);
	LWLOG_API void critical(std::string_view message);
	LWLOG_API void debug(std::string_view message);
}