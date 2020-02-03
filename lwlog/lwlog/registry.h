#pragma once

#include <string>
#include <map>

#include "core.h"

namespace lwlog
{
	template<typename ... SinkPolicyArgs>
	class logger;

	class LWLOG_API registry
	{
	public:
		static registry& instance();

		template<typename Logger>
		void register_logger(Logger logger) 
		{ 
			m_loggers.insert_or_assign(logger->name(), logger); 
		}

		void set_automatic_registry(bool automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		inline bool is_registry_automatic();

		std::shared_ptr<logger<sinks::console_sink>> default_logger() { return m_default_logger; }

	private:
		registry() = default;

	private:
		std::map<std::string, void*> m_loggers;
		bool m_automatic_registry{true};
		std::shared_ptr<logger<sinks::console_sink>> m_default_logger;
	};
}
