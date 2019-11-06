#pragma once

#include "logger.h"

#include "sinks/sink.h"
#include "sinks/console_sink.h"
#include "sinks/file_sink.h"
#include "sinks/sink_factory.h"

namespace lwlog
{
	using console_logger = logger<sinks::console_sink>;
	using file_logger = logger<sinks::file_sink>;

	/*-------------------------------------------*/
	using console_logger_st = nullptr_t;
	using console_logger_mt = nullptr_t;

	using file_logger_st = nullptr_t;
	using file_logger_mt = nullptr_t;
}