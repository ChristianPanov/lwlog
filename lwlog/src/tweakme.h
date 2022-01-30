#pragma once

#define LWLOG_NO_TIME			0
#define LWLOG_USE_LOCALTIME		0
#define LWLOG_USE_THREAD_ID		0
#define LWLOG_USE_PROCESS_ID	0

#define LWLOG_INFO_STR		"info"
#define LWLOG_WARNING_STR	"warning"
#define LWLOG_ERROR_STR		"error"
#define LWLOG_CRITICAL_STR	"critical"
#define LWLOG_DEBUG_STR		"debug"

#define LWLOG_INFO_COLOR		"\u001b[30;1m"
#define LWLOG_WARNING_COLOR		"\u001b[33;1m"
#define LWLOG_ERROR_COLOR		"\u001b[31;1m"
#define LWLOG_CRITICAL_COLOR	"\u001b[41;1m"
#define LWLOG_DEBUG_COLOR		"\u001b[37;1m"