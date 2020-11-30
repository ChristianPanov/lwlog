#pragma once

#include "logger.h"
#include "sinks/file_sink.h"
#include "sinks/stdout_sink.h"
#include "sinks/stdout_color_sink.h"
#include "sinks/stderr_sink.h"
#include "sinks/stderr_color_sink.h"

namespace lwlog
{
	using console_color_logger	= logger<static_storage_policy, sinks::stdout_color_sink>;
	using console_logger		= logger<static_storage_policy, sinks::stdout_sink>;
	using file_logger			= logger<static_storage_policy, sinks::file_sink>;
	using null_logger			= logger<>;

	void register_logger(primitives::logger_ptr logger);
	void automatic_registry(bool automatic);
	void drop(std::string_view logger_name);
	void drop_all();
	void apply_to_all(const std::function<void(primitives::logger_ptr)>& function);
	bool is_registry_automatic();
	const std::unique_ptr<interface::logger>& default_logger();
	primitives::logger_ptr get(std::string_view logger_name);

	void set_pattern(std::string_view pattern);
	void add_pattern_attribute(primitives::attribute_t attribute);
	void set_level_filter(primitives::level_list levels);
	void info(std::string_view message);
	void warning(std::string_view message);
	void error(std::string_view message);
	void critical(std::string_view message);
	void debug(std::string_view message);
}

namespace lwlog::global
{
	void set_pattern(std::string_view pattern);
	void add_pattern_attribute(primitives::attribute_t attribute);
	void set_level_filter(primitives::level_list levels);
}
