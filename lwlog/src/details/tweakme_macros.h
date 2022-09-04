#pragma once

#include "tweakme.h"

#define LWLOG_TIME_FN_WITH_PLACEHOLDER(fn_type, fn_name, arg_type, arg_name)\
fn_type fn_name(void*){ return {}; }\
fn_type fn_name(arg_type arg_name)

#if LWLOG_NO_TIME == 1
#define LWLOG_TIME_TYPE void*
#define LWLOG_INIT_TIME_POINT_FN(...)
#else
#define LWLOG_TIME_TYPE datetime::time_point_t
#define LWLOG_INIT_TIME_POINT_FN(time_point)\
datetime::init_time_point(time_point)
#endif

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