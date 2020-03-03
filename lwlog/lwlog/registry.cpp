#include "registry.h"
#include "logger.h"

namespace lwlog
{
	std::shared_ptr<logger_registry_interface> registry::m_default_logger = std::make_shared<logger<sinks::console_sink>>("");

	registry& registry::instance()
	{
		static registry s_instance;
		return s_instance;
	}

	void registry::register_logger(std::shared_ptr<logger_registry_interface> logger)
	{
		m_loggers[logger->name()] = std::move(logger);
	}

	void registry::set_automatic_registry(bool automatic)
	{
		m_automatic_registry = automatic;
	}

	void registry::drop(std::string_view logger_name)
	{
		m_loggers.erase(logger_name.data());
	}

	void registry::drop_all()
	{
		m_loggers.clear();
	}

	inline bool registry::is_registry_automatic()
	{
		return m_automatic_registry ? true : false;
	}

	std::shared_ptr<logger_registry_interface> registry::get(std::string_view logger_name)
	{
		return m_loggers[logger_name.data()];
	}

	std::shared_ptr<logger_registry_interface> registry::default_logger()
	{
		return m_default_logger;
	}

	void registry::set_default_logger(std::shared_ptr<logger_registry_interface> new_default_logger)
	{
		if (m_default_logger != nullptr)
		{
			m_loggers.erase(m_default_logger->name());
		}

		if (new_default_logger != nullptr)
		{
			m_loggers[new_default_logger->name()] = std::move(new_default_logger);
		}

		m_default_logger = std::move(new_default_logger);
	}
}