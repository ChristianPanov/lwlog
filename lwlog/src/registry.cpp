#include "registry.hpp"
#include "logger.hpp"
#include "sinks/stdout_sink.hpp"

namespace lwlog
{
	registry& registry::instance()
	{
		static registry s_instance;
		return s_instance;
	}

	void registry::init_default_logger()
	{
		s_default_logger = std::make_unique<
			logger<
				forward_log_policy,
				static_storage_policy,
				threading_policy<null_mutex>,
				sinks::stdout_sink
			>
		>("DEFAULT");
	}

	const std::unique_ptr<interface::logger>& registry::default_logger()
	{
		return s_default_logger;
	}

	void registry::register_logger(logger_ptr logger)
	{
		if (logger->name() != "DEFAULT") m_loggers[logger->name()] = logger;
	}

	void registry::set_automatic_registry(bool is_registry_automatic)
	{
		m_is_registry_automatic = is_registry_automatic;
	}

	void registry::drop(std::string_view logger_name)
	{
		m_loggers.erase(logger_name);
	}

	void registry::drop_all()
	{
		m_loggers.clear();
	}

	void registry::apply_to_all(const std::function<void(logger_ptr)>& fn) const
	{
		for (const auto& [name, logger] : m_loggers) fn(logger);
	}

	bool registry::is_registry_automatic() const
	{
		return m_is_registry_automatic;
	}

	const std::unordered_map<std::string_view, logger_ptr>& registry::loggers() const
	{
		return m_loggers;
	}

	logger_ptr registry::get(std::string_view logger_name)
	{
		return m_loggers[logger_name];
	}
}