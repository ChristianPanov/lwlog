#include "registry.h"
#include "lwlog.h"

namespace lwlog
{
	std::unordered_map<std::string, const logger&> registry::m_loggers{};

	void registry::register_logger(const logger& new_logger)
	{
		m_loggers.emplace(new_logger.get_name(), new_logger);
	}

	void registry::drop(std::string logger_name)
	{
		for (auto it = m_loggers.begin(); it != m_loggers.end(); ++it)
		{
			if (it->first == logger_name)
			{
				m_loggers.erase(logger_name);
				break;
			}
		}
	}

	void registry::drop_all()
	{
		m_loggers.clear();
	}

	void registry::set_automatic_registry(bool automatic)
	{
		m_automaticRegistry = automatic;
	}

	void registry::display_all_loggers()
	{
		for (auto it = m_loggers.begin(); it != m_loggers.end(); it++)
		{
			print("{0} \n", it->first);
		}
	}
}
