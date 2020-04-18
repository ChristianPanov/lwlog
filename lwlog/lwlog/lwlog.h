#pragma once

#include <functional>

#include "core.h"
#include "logger.h"

#include "sinks/file_sink.h"
#include "sinks/stdout_sink.h"
#include "sinks/stdout_color_sink.h"
#include "sinks/stderr_sink.h"
#include "sinks/stderr_color_sink.h"

namespace lwlog
{
	using console_color_logger = logger<sinks::stdout_color_sink>;
	using console_logger = logger<sinks::stdout_sink>;
	using file_logger = logger<sinks::file_sink>;

	/*-------------------------------------------*/
	using console_logger_mt = nullptr_t;
	using file_logger_mt = nullptr_t;
	/*-------------------------------------------*/

	LWLOG_API void register_logger(interface::logger_ptr logger);
	LWLOG_API void set_automatic_registry(bool automatic);
	LWLOG_API void drop(std::string_view logger_name);
	LWLOG_API void drop_all();
	LWLOG_API void apply_to_all(const std::function<void(interface::logger_ptr)>& fn);
	LWLOG_API bool is_registry_automatic();
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
	LWLOG_API void dump_backtrace();
}

namespace lwlog::global
{
	LWLOG_API void add_sink(sinks::sink_ptr sink);
	LWLOG_API void remove_sink(sinks::sink_ptr sink);

	LWLOG_API void set_pattern(std::string_view pattern);
	LWLOG_API void add_pattern_attribute(details::pattern_attribute attribute);
	LWLOG_API void set_level_filter(std::initializer_list<sink_level> level_list);

	LWLOG_API void backtrace(std::size_t buffer_size);
	LWLOG_API void disable_backtrace();
	LWLOG_API void set_backtrace_stamp(std::string_view stamp);
	LWLOG_API void display_backtrace();
	LWLOG_API void dump_backtrace();
}