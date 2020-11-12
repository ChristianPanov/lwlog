#pragma once

#include <unordered_map>
#include <memory>
#include <functional>

#include "fwd.h"

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
		void register_logger(interface::logger_ptr logger);
		void automatic_registry(bool automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		void apply_to_all(const std::function<void(interface::logger_ptr)>& function);
		bool is_registry_automatic();

		const std::unique_ptr<interface::logger>& default_logger() const;
		interface::logger_ptr get(std::string_view logger_name);
		std::unordered_map<std::string, interface::logger_ptr> loggers();
		std::unordered_map<std::string, interface::logger_ptr>::iterator begin();
		std::unordered_map<std::string, interface::logger_ptr>::iterator end();
		std::unordered_map<std::string, interface::logger_ptr>::const_iterator cbegin();
		std::unordered_map<std::string, interface::logger_ptr>::const_iterator cend();

	private:
		registry() = default;

	private:
		bool m_automatic_registry{ true };
		static std::unique_ptr<interface::logger> m_default_logger;
		std::unordered_map<std::string, interface::logger_ptr> m_loggers;
	};
}
