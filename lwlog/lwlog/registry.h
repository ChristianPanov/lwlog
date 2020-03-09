#pragma once

#include <unordered_map>
#include <memory>
#include <functional>

#include "core.h"
#include "logger.h"
#include "logger_interface.h"

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
		void register_logger(logger_interface* logger);
		void set_automatic_registry(bool automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		inline bool is_registry_automatic();

		logger_interface* get(std::string_view logger_name);
		std::unordered_map<std::string, logger_interface*> loggers();
		static void apply_to_all(const std::function<void(logger_interface*)>& fn);
		static std::shared_ptr<logger_interface> default_logger();

	private:
		registry() = default;

	private:
		bool m_automatic_registry{true};
		std::unordered_map<std::string, logger_interface*> m_loggers;
		static std::shared_ptr<logger_interface> m_default_logger;
	};
}
