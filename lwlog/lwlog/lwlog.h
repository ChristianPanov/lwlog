#pragma once

#include "logger.h"
#include "sinks/file_sink.h"
#include "sinks/stdout_sink.h"
#include "sinks/stdout_color_sink.h"
#include "sinks/stderr_sink.h"
#include "sinks/stderr_color_sink.h"

namespace lwlog
{
	template<template<typename> typename... Sinks>
	using basic_logger = logger<default_log_policy, default_storage_policy, single_threaded_policy, Sinks...>;
	template<template<typename> typename... Sinks>
	using basic_logger_mt = logger<default_log_policy, default_storage_policy, multi_threaded_policy, Sinks...>;

	using console_color_logger	= basic_logger<sinks::stdout_color_sink>;
	using console_logger		= basic_logger<sinks::stdout_sink>;
	using file_logger			= basic_logger<sinks::file_sink>;

	using console_color_logger_mt	= basic_logger_mt<sinks::stdout_color_sink>;
	using console_logger_mt			= basic_logger_mt<sinks::stdout_sink>;
	using file_logger_mt			= basic_logger_mt<sinks::file_sink>;

	using null_logger		= basic_logger<>;
	using null_logger_mt	= basic_logger_mt<>;
}

namespace lwlog
{
	void register_logger(primitives::logger_ptr logger);
	void automatic_registry(bool automatic);
	void drop(std::string_view logger_name);
	void drop_all();
	void apply_to_all(const std::function<void(primitives::logger_ptr)>& function);
	bool is_registry_automatic();
	const std::unique_ptr<interface::logger>& default_logger();
	primitives::logger_ptr get(std::string_view logger_name);

	void set_pattern(std::string_view pattern);
	void set_level_filter(level t_level);
	void info(std::string_view message);
	void warning(std::string_view message);
	void error(std::string_view message);
	void critical(std::string_view message);
	void debug(std::string_view message);
}

namespace lwlog::global
{
	void set_pattern(std::string_view pattern);
	void set_level_filter(level t_level);
}
