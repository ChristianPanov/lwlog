#include "lwlog.h"

namespace lwlog
{
	void register_logger(primitives::logger_ptr logger)
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

	void apply_to_all(const std::function<void(primitives::logger_ptr)>& function)
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

	primitives::logger_ptr get(std::string_view logger_name)
	{
		return registry::instance().get(logger_name);
	}

	void set_pattern(std::string_view pattern)
	{
		registry::instance().default_logger()->set_pattern(pattern);
	}

	void add_pattern_attribute(primitives::attribute_t attribute)
	{
		registry::instance().default_logger()->add_pattern_attribute(attribute);
	}

	void set_level_filter(level t_level)
	{
		registry::instance().default_logger()->set_level_filter(t_level);
	}

	void info(std::string_view message)
	{
		registry::instance().default_logger()->info(message);
	}

	void warning(std::string_view message)
	{
		registry::instance().default_logger()->warning(message);
	}

	void error(std::string_view message)
	{
		registry::instance().default_logger()->error(message);
	}

	void critical(std::string_view message)
	{
		registry::instance().default_logger()->critical(message);
	}

	void debug(std::string_view message)
	{
		registry::instance().default_logger()->debug(message);
	}
}

namespace lwlog::global
{
	void set_pattern(std::string_view pattern)
	{
		registry::instance().apply_to_all([pattern](primitives::logger_ptr logger)
			{
				logger->set_pattern(pattern);
			});
	}

	void add_pattern_attribute(primitives::attribute_t attribute)
	{
		registry::instance().apply_to_all([attribute](primitives::logger_ptr logger)
			{
				logger->add_pattern_attribute(attribute);
			});
	}

	void set_level_filter(level t_level)
	{
		registry::instance().apply_to_all([t_level](primitives::logger_ptr logger)
			{
				logger->set_level_filter(t_level);
			});
	}
}