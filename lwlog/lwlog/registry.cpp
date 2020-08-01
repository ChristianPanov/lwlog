#include "registry.h"
#include "logger.h"
#include "sinks/stdout_color_sink.h"

namespace lwlog
{
	std::shared_ptr<interface::logger> registry::m_default_logger 
		= std::make_shared<logger<sinks::stdout_color_sink>>("");

	registry& registry::instance()
	{
		static registry s_instance;
		return s_instance;
	}

	void registry::register_logger(interface::logger_ptr logger)
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
		m_loggers.erase(logger_name.data());
	}

	void registry::drop_all()
	{
		m_loggers.clear();
	}

	void registry::apply_to_all(const std::function<void(interface::logger_ptr)>& fn)
	{
		for (const auto& [name, logger] : registry::instance().loggers())
		{
			if (!name.empty())
			{
				fn(logger);
			}
		}
	}

	bool registry::is_registry_automatic()
	{
		return m_automatic_registry;
	}

	interface::logger_ptr registry::get(std::string_view logger_name)
	{
		return m_loggers[logger_name.data()];
	}

	std::unordered_map<std::string, interface::logger_ptr> registry::loggers()
	{
		return m_loggers;
	}

	std::shared_ptr<interface::logger> registry::default_logger()
	{
		return m_default_logger;
	}
}