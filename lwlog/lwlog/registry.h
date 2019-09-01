#pragma once

#include <string>
#include <map>

#include "core.h"

namespace lwlog 
{
	class logger;

	class LWLOG_API registry 
	{
	public:
		static void register_logger(const logger& new_logger);

		static void drop(std::string logger_name);
		static void drop_all();

		static void set_automatic_registry(bool automatic);

		static void display_all_loggers();

		static inline bool is_registry_automatic() { return m_automaticRegistry ? true : false; }

	private:
		static std::map<std::string, logger> m_loggers;
		static bool m_automaticRegistry;
	};
}
