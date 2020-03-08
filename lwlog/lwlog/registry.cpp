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

	void registry::register_logger(logger_registry_interface* logger)
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

	logger_registry_interface* registry::get(std::string_view logger_name)
	{
		return m_loggers[logger_name.data()];
	}

	std::unordered_map<std::string, logger_registry_interface*> registry::loggers()
	{
		return m_loggers;
	}

	void registry::apply_to_all(const std::function<void(logger_registry_interface*)>& fn)
	{
		for (const auto& [name, logger] : registry::instance().loggers())
		{
			if (!name.empty())
			{
				fn(logger);
			}
		}
	}

	std::shared_ptr<logger_registry_interface> registry::default_logger()
	{
		return m_default_logger;
	}
}