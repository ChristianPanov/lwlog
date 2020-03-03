#pragma once

#include <map>
#include <memory>

#include "core.h"
#include "logger.h"
#include "logger_registry_interface.h"

namespace lwlog
{
	class LWLOG_API registry
	{
		registry(const registry&) = delete;
		registry(registry&&) = delete;
		registry& operator=(const registry&) = delete;
		registry& operator=(registry&&) = delete;

	public:
		static registry& instance();
		void register_logger(std::shared_ptr<logger_registry_interface> logger);
		void set_automatic_registry(bool automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		inline bool is_registry_automatic();

		std::shared_ptr<logger_registry_interface> get(std::string_view logger_name);
		static std::shared_ptr<logger_registry_interface> default_logger();
		void set_default_logger(std::shared_ptr<logger_registry_interface> new_default_logger);

	private:
		registry() = default;

	private:
		bool m_automatic_registry{true};
		std::map<std::string, std::shared_ptr<logger_registry_interface>> m_loggers;
		static std::shared_ptr<logger_registry_interface> m_default_logger;
	};
}
