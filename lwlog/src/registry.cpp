#include "registry.h"
#include "logger.h"
#include "sinks/stdout_sink.h"

namespace lwlog
{
	std::unique_ptr<interface::logger> registry::m_default_logger =
		std::make_unique<logger<
		default_log_policy,
		static_storage_policy,
		single_threaded_policy,
		sinks::stdout_sink
		>>("");

	registry& registry::instance()
	{
		static registry s_instance;
		return s_instance;
	}

	void registry::register_logger(primitives::logger_ptr logger)
	{
		if (m_automatic_registry && !logger->name().empty())
		{
			m_loggers[logger->name()] = std::move(logger);
		}
	}

	void registry::automatic_registry(bool automatic)
	{
		m_automatic_registry = automatic;
	}

	void registry::drop(std::string_view logger_name)
	{
		m_loggers.erase(logger_name);
	}

	void registry::drop_all()
	{
		m_loggers.clear();
	}

	void registry::apply_to_all(const std::function<void(primitives::logger_ptr)>& function)
	{
		for (const auto& [name, logger] : m_loggers)
		{
			if (!name.empty()) function(logger);
		}
	}

	bool registry::is_registry_automatic()
	{
		return m_automatic_registry;
	}

	const std::unique_ptr<interface::logger>& registry::default_logger() const
	{
		return m_default_logger;
	}

	const std::unordered_map<std::string_view, primitives::logger_ptr>& registry::loggers() const
	{
		return m_loggers;
	}

	primitives::logger_ptr registry::get(std::string_view logger_name)
	{
		return m_loggers[logger_name];
	}
}