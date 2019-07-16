#pragma once

#include <unordered_map>

#include "core.h"

namespace lwlog
{
	class logger;

	class LWLOG_API registry final
	{
	private:
		static std::unordered_map<std::string, const logger&> m_loggers;
		static inline bool m_automaticRegistry = true;

	public:
		registry() = delete;
		registry(const registry&) = delete;
		registry(registry&&) = delete;
		registry& operator=(const registry&) = delete;
		registry& operator=(registry&&) = delete;

		static void register_logger(const logger& new_logger);

		static void drop(std::string logger_name);
		static void drop_all();

		static void set_automatic_registry(bool automatic);

		static void display_all_loggers();

		static inline bool is_registry_automatic() { return m_automaticRegistry ? true : false; }
	};
}
