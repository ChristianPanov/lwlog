#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

#include "core.h"

namespace lwlog
{
	class logger;

	class LWLOG registry
	{
	private:
		registry() {}
		std::unordered_map<std::string, logger*> m_loggersMap;
		bool m_automatic_registry = true;

	public:
		registry(const registry&) = delete;
		registry& operator=(const registry&) = delete;

		void register_logger(logger* new_logger);

		void drop(const std::string& logger_name);
		void drop_all();

		void set_automatic_registry(bool automatic);

		void display_all_loggers();

		inline bool is_registry_automatic() { return m_automatic_registry ? true : false; }

		static registry& instance()
		{
			static registry s_instance;
			return s_instance;
		}
	};
}
