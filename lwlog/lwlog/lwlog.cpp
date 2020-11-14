#include "lwlog.h"

namespace lwlog
{
	void register_logger(interface::logger_ptr logger)
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

	void apply_to_all(const std::function<void(interface::logger_ptr)>& function)
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

	interface::logger_ptr get(std::string_view logger_name)
	{
		return registry::instance().get(logger_name);
	}

	void set_pattern(std::string_view pattern)
	{
		registry::instance().default_logger()->set_pattern(pattern);
	}

	void add_pattern_attribute(details::attribute_t attribute)
	{
		registry::instance().default_logger()->add_pattern_attribute(attribute);
	}

	void set_level_filter(std::initializer_list<sink_level> level_list)
	{
		registry::instance().default_logger()->set_level_filter(level_list);
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
	void add_sink(sinks::sink_ptr sink)
	{
		registry::instance().apply_to_all([sink](interface::logger_ptr logger)
			{
				logger->add_sink(sink);
			});
	}

	void remove_sink(sinks::sink_ptr sink)
	{
		registry::instance().apply_to_all([sink](interface::logger_ptr logger)
			{
				logger->remove_sink(sink);
			});
	}

	void set_pattern(std::string_view pattern)
	{
		registry::instance().apply_to_all([pattern](interface::logger_ptr logger)
			{
				logger->set_pattern(pattern);
			});
	}

	void add_pattern_attribute(details::attribute_t attribute)
	{
		registry::instance().apply_to_all([attribute](interface::logger_ptr logger)
			{
				logger->add_pattern_attribute(attribute);
			});
	}

	void set_level_filter(std::initializer_list<sink_level> level_list)
	{
		registry::instance().apply_to_all([level_list](interface::logger_ptr logger)
			{
				logger->set_level_filter(level_list);
			});
	}
}