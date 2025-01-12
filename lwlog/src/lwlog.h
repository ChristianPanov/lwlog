#pragma once

#include "logger.h"
#include "sinks/file_sink.h"
#include "sinks/stdout_sink.h"
#include "sinks/stderr_sink.h"

namespace lwlog
{
	using default_config = configuration<disable_local_time, enable_thread_id,
		enable_process_id, enable_topics>;

	using default_overflow_policy = block_overflow_policy;
	using default_flush_policy = immediate_flush_policy;

	template<template<typename, typename> typename... Sinks>
	using basic_logger = logger<default_config, synchronous_policy, immediate_flush_policy, 
		single_threaded_policy, Sinks...>;

	template<template<typename, typename> typename... Sinks>
	using basic_logger_mt = logger<default_config, synchronous_policy, immediate_flush_policy, 
		multi_threaded_policy, Sinks...>;

	template<template<typename, typename> typename... Sinks>
	using async_logger = logger<default_config, asynchronous_policy<>, immediate_flush_policy, 
		single_threaded_policy, Sinks...>;

	template<template<typename, typename> typename... Sinks>
	using async_logger_mt = logger<default_config, asynchronous_policy<>, immediate_flush_policy, 
		multi_threaded_policy, Sinks...>;

	using console_logger			= basic_logger<sinks::stdout_sink>;
	using console_logger_mt			= basic_logger_mt<sinks::stdout_sink>;
	using file_logger				= basic_logger<sinks::file_sink>;
	using file_logger_mt			= basic_logger_mt<sinks::file_sink>;

	using async_console_logger		= async_logger<sinks::stdout_sink>;
	using async_console_logger_mt	= async_logger_mt<sinks::stdout_sink>;
	using async_file_logger			= async_logger<sinks::file_sink>;
	using async_file_logger_mt		= async_logger_mt<sinks::file_sink>;
}

#ifndef LWLOG_DISABLE
#define LWLOG_INIT_DEFAULT_LOGGER() lwlog::init_default_logger()
#else
#define LWLOG_INIT_DEFAULT_LOGGER()
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_SET_LEVEL_FILTER(level) lwlog::set_level_filter(level)
#else
#define LWLOG_SET_LEVEL_FILTER()
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_SET_PATTERN(pattern) lwlog::set_pattern(pattern)
#else
#define LWLOG_SET_PATTERN()
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_SET_TOPIC_SEPARATOR(separator) lwlog::set_topic_separator(separator)
#else
#define LWLOG_SET_TOPIC_SEPARATOR()
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_START_TOPIC(topic) lwlog::start_topic(topic)
#else
#define LWLOG_START_TOPIC()
#endif

#ifndef LWLOG_DISABLE
#define LWLOG_END_TOPIC() lwlog::end_topic()
#else
#define LWLOG_END_TOPIC()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_INFO_OFF)
#define LWLOG_INFO(...) lwlog::info(__VA_ARGS__)
#else
#define LWLOG_INFO()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_WARNING_OFF)
#define LWLOG_WARNING(...) lwlog::warning(__VA_ARGS__)
#else
#define LWLOG_WARNING()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_ERROR_OFF)
#define LWLOG_ERROR(...) lwlog::error(__VA_ARGS__)
#else
#define LWLOG_ERROR()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_CRITICAL_OFF)
#define LWLOG_CRITICAL(...) lwlog::critical(__VA_ARGS__)
#else
#define LWLOG_CRITICAL()
#endif

#if !defined(LWLOG_DISABLE) && !defined(LWLOG_DEBUG_OFF)
#define LWLOG_DEBUG(...) lwlog::debug(__VA_ARGS__)
#else
#define LWLOG_DEBUG()
#endif

#include "lwlog_impl.h"