#pragma once

#include "logger.h"
#include "sinks/file_sink.h"
#include "sinks/stdout_sink.h"
#include "sinks/stderr_sink.h"
#include "details/topic.h"

namespace lwlog
{
	template<template<typename, typename> typename... Sinks>
	using basic_logger = logger<default_config, synchronous_policy, immediate_flush_policy, single_threaded_policy, Sinks...>;
	template<template<typename, typename> typename... Sinks>
	using basic_logger_mt = logger<default_config, synchronous_policy, immediate_flush_policy, multi_threaded_policy, Sinks...>;

	template<template<typename, typename> typename... Sinks>
	using async_logger = logger<default_config, asynchronous_policy<>, immediate_flush_policy, single_threaded_policy, Sinks...>;
	template<template<typename, typename> typename... Sinks>
	using async_logger_mt = logger<default_config, asynchronous_policy<>, immediate_flush_policy, multi_threaded_policy, Sinks...>;

	using console_logger			= basic_logger<sinks::stdout_sink>;
	using console_logger_mt			= basic_logger_mt<sinks::stdout_sink>;
	//using file_logger				= basic_logger<sinks::file_sink>;
	//using file_logger_mt			= basic_logger_mt<sinks::file_sink>;

	using async_console_logger		= async_logger<sinks::stdout_sink>;
	using async_console_logger_mt	= async_logger_mt<sinks::stdout_sink>;
	//using async_file_logger			= async_logger<sinks::file_sink>;
	//using async_file_logger_mt		= async_logger_mt<sinks::file_sink>;

	using default_overflow_policy	= block_overflow_policy;
	using default_flush_policy		= immediate_flush_policy;
}

namespace lwlog
{
	void init_default_logger();
	void register_logger(logger_ptr logger);
	void set_automatic_registry(bool is_registry_automatic);
	void drop(std::string_view logger_name);
	void drop_all();
	void apply_to_all(const std::function<void(logger_ptr)>& function);
	bool is_registry_automatic();
	const std::unique_ptr<interface::logger>& default_logger();
	logger_ptr get(std::string_view logger_name);

	void set_pattern(std::string_view pattern);
	void set_level_filter(level log_level);

	void start_topic(std::string_view name);
	void end_topic();

	template<typename... Args> void info(const details::log_message& log_msg, Args&&... args);
	template<typename... Args> void warning(const details::log_message& log_msg, Args&&... args);
	template<typename... Args> void error(const details::log_message& log_msg, Args&&... args);
	template<typename... Args> void critical(const details::log_message& log_msg, Args&&... args);
	template<typename... Args> void debug(const details::log_message& log_msg, Args&&... args);
}

#ifndef LWLOG_DISABLE
#define LWLOG_INIT_DEFAULT_LOGGER()\
lwlog::init_default_logger()
#else
#define LWLOG_INIT_DEFAULT_LOGGER()
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_SET_PATTERN(pattern)\
lwlog::set_pattern(pattern)
#else
#define LWLOG_SET_PATTERN()
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_SET_LEVEL_FILTER(level)\
lwlog::set_level_filter(level)
#else
#define LWLOG_SET_LEVEL_FILTER()
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_START_TOPIC(topic)\
lwlog::start_topic(topic)
#else
#define LWLOG_START_TOPIC()
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_END_TOPIC()\
lwlog::end_topic()
#else
#define LWLOG_END_TOPIC()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_INFO_OFF)
#define LWLOG_INFO(...)\
lwlog::info(__VA_ARGS__)
#else
#define LWLOG_INFO()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_WARNING_OFF)
#define LWLOG_WARNING(...)\
lwlog::warning(__VA_ARGS__)
#else
#define LWLOG_WARNING()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_ERROR_OFF)
#define LWLOG_ERROR(...)\
lwlog::error(__VA_ARGS__)
#else
#define LWLOG_ERROR()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_CRITICAL_OFF)
#define LWLOG_CRITICAL(...)\
lwlog::critical(__VA_ARGS__)
#else
#define LWLOG_CRITICAL()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_DEBUG_OFF)
#define LWLOG_DEBUG(...)\
lwlog::debug(__VA_ARGS__)
#else
#define LWLOG_DEBUG()
#endif

#include "lwlog_impl.h"