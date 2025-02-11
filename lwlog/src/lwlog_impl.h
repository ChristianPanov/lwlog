#pragma once

#include "registry.h"
#include "lwlog.h"

namespace lwlog
{
	void init_default_logger()
	{
		registry::init_default_logger();
	}

	void register_logger(logger_ptr logger)
	{
		registry::instance().register_logger(logger);
	}

	void set_automatic_registry(bool is_registry_automatic)
	{
		registry::instance().set_automatic_registry(is_registry_automatic);
	}

	void drop(std::string_view logger_name)
	{
		registry::instance().drop(logger_name);
	}

	void drop_all()
	{
		registry::instance().drop_all();
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
		return registry::default_logger();
	}

	logger_ptr get(std::string_view logger_name)
	{
		return registry::instance().get(logger_name);
	}

	void set_level_filter(level log_level)
	{
		registry::default_logger()->set_level_filter(log_level);
	}

	void set_pattern(std::string_view pattern)
	{
		registry::default_logger()->set_pattern(pattern);
	}

	void set_topic_separator(std::string_view separator)
	{
		registry::default_logger()->set_topic_separator(separator);
	}

	void start_topic(std::string_view name)
	{
		registry::default_logger()->start_topic(name);
	}

	void end_topic()
	{
		registry::default_logger()->end_topic();
	}

	template<typename... Args>
	void info(const details::log_message& log_msg, Args&&... args)
	{
		registry::default_logger()->info(log_msg, std::forward<Args>(args)...);
	}

	template<typename... Args>
	void warning(const details::log_message& log_msg, Args&&... args)
	{
		registry::default_logger()->warning(log_msg, std::forward<Args>(args)...);
	}

	template<typename... Args>
	void error(const details::log_message& log_msg, Args&&... args)
	{
		registry::default_logger()->error(log_msg, std::forward<Args>(args)...);
	}

	template<typename... Args>
	void critical(const details::log_message& log_msg, Args&&... args)
	{
		registry::default_logger()->critical(log_msg, std::forward<Args>(args)...);
	}

	template<typename... Args>
	void debug(const details::log_message& log_msg, Args&&... args)
	{
		registry::default_logger()->debug(log_msg, std::forward<Args>(args)...);
	}
}
