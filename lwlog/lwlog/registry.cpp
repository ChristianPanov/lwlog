#include "registry.h"

#include "lwlog.h"

namespace lwlog
{
	void registry::register_logger(logger* new_logger)
	{
		m_loggersMap.emplace(new_logger->get_name(), new_logger);
	}

	void registry::drop(const std::string& logger_name)
	{
		for (auto it = m_loggersMap.begin(); it != m_loggersMap.end(); ++it)
		{
			if (it->first == logger_name)
			{
				m_loggersMap.erase(logger_name);
				break;
			}
		}
	}

	void registry::drop_all()
	{
		m_loggersMap.clear();
	}

	void registry::set_automatic_registry(bool automatic)
	{
		m_automatic_registry = automatic;
	}

	void registry::display_all_loggers()
	{
		for (auto it = m_loggersMap.begin(); it != m_loggersMap.end(); it++)
		{
			print("{0} \n", it->first);
		}
	}
}
