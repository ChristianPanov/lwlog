#pragma once

#include <functional>

#include "core.h"
#include "logger.h"

namespace lwlog
{
	using console_logger = logger<sinks::console_sink>;
	using file_logger = logger<sinks::file_sink>;

	/*-------------------------------------------*/
	using console_logger_mt = nullptr_t;
	using file_logger_mt = nullptr_t;
	/*-------------------------------------------*/

	LWLOG_API interface::logger_ptr get(std::string_view logger_name);
	LWLOG_API std::shared_ptr<interface::logger> default_logger();

	LWLOG_API void add_pattern_attribute(details::pattern_attribute attribute);

	LWLOG_API void info(std::string_view message);
	LWLOG_API void warning(std::string_view message);
	LWLOG_API void error(std::string_view message);
	LWLOG_API void critical(std::string_view message);
	LWLOG_API void debug(std::string_view message);

	LWLOG_API void backtrace(std::size_t buffer_size);
	LWLOG_API void disable_backtrace();
	LWLOG_API void set_backtrace_stamp(std::string_view stamp);
	LWLOG_API void display_backtrace();
	LWLOG_API void delete_backtrace();

	LWLOG_API void apply_to_all(const std::function<void(interface::logger_ptr)>& fn);
}

namespace lwlog::global
{
	LWLOG_API void add_sink(sinks::sink_ptr sink);
	LWLOG_API void remove_sink(sinks::sink_ptr sink);

	LWLOG_API void set_pattern(std::string_view pattern);
	LWLOG_API void add_pattern_attribute(details::pattern_attribute attribute);
	LWLOG_API void set_level_visibility(std::initializer_list<sink_level> level_list);

	LWLOG_API void backtrace(std::size_t buffer_size);
	LWLOG_API void disable_backtrace();
	LWLOG_API void set_backtrace_stamp(std::string_view stamp);
	LWLOG_API void display_backtrace();
	LWLOG_API void delete_backtrace();
}