#pragma once

#include "logger.h"
#include "sinks/file_sink.h"
#include "sinks/stdout_sink.h"
#include "sinks/stderr_sink.h"
#include "buffer_limits.h"

namespace lwlog
{
	using default_config = configuration<disable_local_time, enable_thread_id,
		enable_process_id, enable_topics>;

	using default_overflow_policy = block_overflow_policy;
	using default_flush_policy = immediate_flush_policy;

	template<template<typename, typename, typename, typename> typename... Sinks>
	using basic_logger = logger<default_config, default_memory_buffer_limits, 
		synchronous_policy, immediate_flush_policy, single_threaded_policy, Sinks...>;

	template<template<typename, typename, typename, typename> typename... Sinks>
	using basic_logger_mt = logger<default_config, default_memory_buffer_limits, 
		synchronous_policy, immediate_flush_policy, multi_threaded_policy, Sinks...>;

	template<template<typename, typename, typename, typename> typename... Sinks>
	using async_logger = logger<default_config, default_memory_buffer_limits, 
		asynchronous_policy<>, immediate_flush_policy, single_threaded_policy, Sinks...>;

	template<template<typename, typename, typename, typename> typename... Sinks>
	using async_logger_mt = logger<default_config, default_memory_buffer_limits, 
		asynchronous_policy<>, immediate_flush_policy, multi_threaded_policy, Sinks...>;

	using console_logger			= basic_logger<sinks::stdout_sink>;
	using console_logger_mt			= basic_logger_mt<sinks::stdout_sink>;
	using file_logger				= basic_logger<sinks::file_sink>;
	using file_logger_mt			= basic_logger_mt<sinks::file_sink>;

	using async_console_logger		= async_logger<sinks::stdout_sink>;
	using async_console_logger_mt	= async_logger_mt<sinks::stdout_sink>;
	using async_file_logger			= async_logger<sinks::file_sink>;
	using async_file_logger_mt		= async_logger_mt<sinks::file_sink>;
}