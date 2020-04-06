#pragma once

#include <unordered_map>
#include <memory>
#include <functional>

#include "core.h"
#include "fwd.h"

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
		void register_logger(interface::logger* logger);
		void set_automatic_registry(bool automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		inline bool is_registry_automatic();

		interface::logger* get(std::string_view logger_name);
		std::unordered_map<std::string, interface::logger*> loggers();
		static void apply_to_all(const std::function<void(interface::logger*)>& fn);
		static std::shared_ptr<interface::logger> default_logger();

	private:
		registry() = default;

	public:
		bool m_automatic_registry{ true };
		std::unordered_map<std::string, interface::logger*> m_loggers;
		static std::shared_ptr<interface::logger> m_default_logger;
	};
}
