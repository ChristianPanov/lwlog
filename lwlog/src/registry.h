#pragma once

#include <functional>

#include "fwd.h"
#include "interface/logger_interface.h"

namespace lwlog
{
	class registry
	{
	private:
		registry(const registry&) = delete;
		registry(registry&&) = delete;
		registry& operator=(const registry&) = delete;
		registry& operator=(registry&&) = delete;

	public:
		static registry& instance();
		void register_logger(logger_ptr logger);
		void automatic_registry(bool automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		void apply_to_all(const std::function<void(logger_ptr)>& function);
		bool is_registry_automatic();
		const std::unique_ptr<interface::logger>& default_logger() const;
		const std::unordered_map<std::string_view, logger_ptr>& loggers() const;
		logger_ptr get(std::string_view logger_name);

	private:
		registry() = default;

	private:
		bool m_automatic_registry{ true };
		static std::unique_ptr<interface::logger> m_default_logger;
		std::unordered_map<std::string_view, logger_ptr> m_loggers;
	};
}
