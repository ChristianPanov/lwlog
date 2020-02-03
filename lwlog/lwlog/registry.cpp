#include "registry.h"
#include "logger.h"

namespace lwlog
{
	registry& registry::instance()
	{
		static registry s_instance;
		return s_instance;
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

	std::shared_ptr<logger<sinks::console_sink>>& registry::default_logger()
	{
		return m_default_logger;
	}
}