#pragma once

#include "logger.h"
#include "sinks/file_sink.h"
#include "sinks/stdout_sink.h"
#include "sinks/stderr_sink.h"

namespace lwlog
{
	template<template<typename> typename... Sinks>
	using basic_logger = logger<default_log_policy, default_storage_policy, single_threaded_policy, Sinks...>;
	template<template<typename> typename... Sinks>
	using basic_logger_mt = logger<default_log_policy, default_storage_policy, multi_threaded_policy, Sinks...>;

	using console_logger = basic_logger<sinks::stdout_sink>;
	using file_logger = basic_logger<sinks::file_sink>;

	using console_logger_mt	= basic_logger_mt<sinks::stdout_sink>;
	using file_logger_mt = basic_logger_mt<sinks::file_sink>;

	using null_logger = basic_logger<>;
	using null_logger_mt = basic_logger_mt<>;
}

namespace lwlog
{
	void register_logger(logger_ptr logger);
	void automatic_registry(bool automatic);
	void drop(std::string_view logger_name);
	void drop_all();
	void apply_to_all(const std::function<void(logger_ptr)>& function);
	bool is_registry_automatic();
	const std::unique_ptr<interface::logger>& default_logger();
	logger_ptr get(std::string_view logger_name);

	void set_pattern(std::string_view pattern);
	void set_level_filter(level t_level);
	void info(std::string_view message);
	void warning(std::string_view message);
	void error(std::string_view message);
	void critical(std::string_view message);
	void debug(std::string_view message);
}

#ifndef LWLOG_DISABLE
#define LWLOG_SET_PATTERN(pattern) \
lwlog::set_pattern(pattern)
#else
#define LWLOG_SET_PATTERN(pattern)
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_SET_LEVEL_FILTER(...) \
lwlog::set_level_filter(__VA__ARGS)
#else
#define LWLOG_SET_LEVEL_FILTER(...)
#endif

#ifndef LWLOG_DISABLE && LWLOG_INFO_OFF
#define LWLOG_INFO(...)	\
lwlog::info(__VA_ARGS__)
#else
#define LWLOG_INFO(...)
#endif

#ifndef LWLOG_DISABLE && LWLOG_WARNING_OFF
#define LWLOG_WARNING(...) \
lwlog::warning(__VA_ARGS__)
#else
#define LWLOG_WARNING(...)
#endif

#ifndef LWLOG_DISABLE && LWLOG_ERROR_OFF
#define LWLOG_ERROR(...) \
lwlog::error(__VA_ARGS__)
#else
#define LWLOG_ERROR(...)
#endif

#ifndef LWLOG_DISABLE && LWLOG_CRITICAL_OFF
#define LWLOG_CRITICAL(...) \
lwlog::critical(__VA_ARGS__)
#else
#define LWLOG_CRITICAL(...)
#endif

#ifndef LWLOG_DISABLE && LWLOG_DEBUG_OFF
#define LWLOG_DEBUG(...) \
lwlog::debug(__VA_ARGS__)
#else
#define LWLOG_DEBUG(...)
#endif