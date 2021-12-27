#include "lwlog.h"

namespace lwlog
{
	void register_logger(logger_ptr logger)
	{
		return registry::instance().register_logger(logger);
	}

	void automatic_registry(bool automatic)
	{
		return registry::instance().automatic_registry(automatic);
	}

	void drop(std::string_view logger_name)
	{
		return registry::instance().drop(logger_name);
	}

	void drop_all()
	{
		return registry::instance().drop_all();
	}

	void apply_to_all(const std::function<void(logger_ptr)>& function)
	{
		registry::instance().apply_to_all(function);
	}

	bool is_registry_automatic()
	{
		return registry::instance().is_registry_automatic();
	}

	const std::unique_ptr<interface::logger>& default_logger()
	{
		return registry::instance().default_logger();
	}

	logger_ptr get(std::string_view logger_name)
	{
		return registry::instance().get(logger_name);
	}

	void set_pattern(std::string_view pattern)
	{
		registry::instance().default_logger()->set_pattern(pattern);
	}

	void set_level_filter(level t_level)
	{
		registry::instance().default_logger()->set_level_filter(t_level);
	}

	void info(std::string_view message, details::source_meta meta)
	{
		registry::instance().default_logger()->info(message, meta);
	}

	void warning(std::string_view message, details::source_meta meta)
	{
		registry::instance().default_logger()->warning(message, meta);
	}

	void error(std::string_view message, details::source_meta meta)
	{
		registry::instance().default_logger()->error(message, meta);
	}

	void critical(std::string_view message, details::source_meta meta)
	{
		registry::instance().default_logger()->critical(message, meta);
	}

	void debug(std::string_view message, details::source_meta meta)
	{
		registry::instance().default_logger()->debug(message, meta);
	}
}