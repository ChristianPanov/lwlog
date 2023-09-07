#pragma once

#include "tweakme.h"

#if LWLOG_USE_THREAD_ID == 1
	#define LWLOG_THREAD_ID_TYPE std::size_t
	#define LWLOG_THREAD_ID_FN(...) os::thread_id()
#else
	#define LWLOG_THREAD_ID_TYPE void*
	#define LWLOG_THREAD_ID_FN(...) nullptr
#endif

#if LWLOG_USE_PROCESS_ID == 1
	#define LWLOG_PROCESS_ID_TYPE std::size_t
	#define LWLOG_PROCESS_ID_FN(...) os::process_id()
#else
	#define LWLOG_PROCESS_ID_TYPE void*
	#define LWLOG_PROCESS_ID_FN(...) nullptr
#endif

#if LWLOG_NO_FORMATTING == 1
	#define LWLOG_FORMAT_FN(x, ...) x
#else
	#if LWLOG_USE_FMT == 1
		#include <fmt/format.h>
		#define LWLOG_FORMAT_FN(x, ...) fmt::format(x, __VA_ARGS__)
	#elif LWLOG_USE_STD_FORMAT == 1
		#if __cplusplus < 202002L
			#error "std::format is not supported in current cpp standard"
		#else
			#include <format>
			#define LWLOG_FORMAT_FN(x, ...) std::format(x, __VA_ARGS__)
		#endif
	#else
		#define LWLOG_FORMAT_FN(x, ...) lwlog::details::format_arguments(x, __VA_ARGS__)
	#endif
#endif