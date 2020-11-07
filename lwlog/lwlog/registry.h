#pragma once

#include <unordered_map>
#include <memory>
#include <functional>

#include "fwd.h"

namespace lwlog
{
	class registry
	{
		registry(const registry&) = delete;
		registry(registry&&) = delete;
		registry& operator=(const registry&) = delete;
		registry& operator=(registry&&) = delete;

	public:
		static registry& instance();
		void register_logger(interface::logger_ptr logger);
		void automatic_registry(bool automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		void apply_to_all(const std::function<void(interface::logger_ptr)>& fn);
		bool is_registry_automatic();

		interface::logger_ptr get(std::string_view logger_name);
		std::unordered_map<std::string, interface::logger_ptr> loggers();
		const std::unique_ptr<interface::logger>& default_logger() const;

	private:
		registry() = default;

	private:
		bool m_automatic_registry{ true };
		std::unordered_map<std::string, interface::logger_ptr> m_loggers;
		static std::unique_ptr<interface::logger> m_default_logger;
	};
}
