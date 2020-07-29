#pragma once

#include <functional>

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

	void register_logger(interface::logger_ptr logger);
	void set_automatic_registry(bool automatic);
	void drop(std::string_view logger_name);
	void drop_all();
	void apply_to_all(const std::function<void(interface::logger_ptr)>& fn);
	bool is_registry_automatic();
	interface::logger_ptr get(std::string_view logger_name);
	std::shared_ptr<interface::logger> default_logger();

	void add_pattern_attribute(details::pattern_attribute attribute);
	void info(std::string_view message);
	void warning(std::string_view message);
	void error(std::string_view message);
	void critical(std::string_view message);
	void debug(std::string_view message);

	void backtrace(std::size_t chunk_size, std::size_t chunks);
	void disable_backtrace();
	void set_backtrace_stamp(std::string_view stamp);
	void display_backtrace();
	void dump_backtrace();
}

namespace lwlog::global
{
	void add_sink(sinks::sink_ptr sink);
	void remove_sink(sinks::sink_ptr sink);

	void set_pattern(std::string_view pattern);
	void add_pattern_attribute(details::pattern_attribute attribute);
	void set_level_filter(std::initializer_list<sink_level> level_list);

	void backtrace(std::size_t chunk_size, std::size_t chunks);
	void disable_backtrace();
	void set_backtrace_stamp(std::string_view stamp);
	void display_backtrace();
	void dump_backtrace();
}