#pragma once

#include "logger.h"
#include "sinks/file_sink.h"
#include "sinks/stdout_sink.h"
#include "sinks/stderr_sink.h"

namespace lwlog
{
	template<typename... Args>
	using default_storage_policy	= dynamic_storage_policy<Args...>;
	using default_log_policy		= forward_log_policy;
	using single_threaded_policy	= threading_policy<null_mutex>;
	using multi_threaded_policy		= threading_policy<std::mutex>;

	template<template<typename> typename... Sinks>
	using basic_logger = logger<default_log_policy, default_storage_policy, single_threaded_policy, Sinks...>;
	template<template<typename> typename... Sinks>
	using basic_logger_mt = logger<default_log_policy, default_storage_policy, multi_threaded_policy, Sinks...>;

	using console_logger	= basic_logger<sinks::stdout_sink>;
	using console_logger_mt	= basic_logger_mt<sinks::stdout_sink>;

	using file_logger		= basic_logger<sinks::file_sink>;
	using file_logger_mt	= basic_logger_mt<sinks::file_sink>;

	using null_logger		= basic_logger<>;
	using null_logger_mt	= basic_logger_mt<>;
}

namespace lwlog
{
	void register_logger(logger_ptr logger);
	void set_automatic_registry(bool is_registry_automatic);
	void drop(std::string_view logger_name);
	void drop_all();
	void apply_to_all(const std::function<void(logger_ptr)>& function);
	bool is_registry_automatic();
	const std::unique_ptr<interface::logger>& default_logger();
	logger_ptr get(std::string_view logger_name);

	void set_pattern(std::string_view pattern);
	void set_level_filter(level t_level);

	void info(std::string_view message, details::source_meta meta = details::source_meta::current());
	void warning(std::string_view message, details::source_meta meta = details::source_meta::current());
	void error(std::string_view message, details::source_meta meta = details::source_meta::current());
	void critical(std::string_view message, details::source_meta meta = details::source_meta::current());
	void debug(std::string_view message, details::source_meta meta = details::source_meta::current());
}

#ifndef LWLOG_DISABLE
#define LWLOG_SET_PATTERN(pattern) \
lwlog::set_pattern(pattern)
#else
#define LWLOG_SET_PATTERN
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_SET_LEVEL_FILTER(level) \
lwlog::set_level_filter(level)
#else
#define LWLOG_SET_LEVEL_FILTER
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_INFO_OFF)
#define LWLOG_INFO(...)	\
lwlog::info(__VA_ARGS__)
#else
#define LWLOG_INFO
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_WARNING_OFF)
#define LWLOG_WARNING(...) \
lwlog::warning(__VA_ARGS__)
#else
#define LWLOG_WARNING
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_ERROR_OFF)
#define LWLOG_ERROR(...) \
lwlog::error(__VA_ARGS__)
#else
#define LWLOG_ERROR
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_CRITICAL_OFF)
#define LWLOG_CRITICAL(...) \
lwlog::critical(__VA_ARGS__)
#else
#define LWLOG_CRITICAL
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_DEBUG_OFF)
#define LWLOG_DEBUG(...) \
lwlog::debug(__VA_ARGS__)
#else
#define LWLOG_DEBUG
#endif