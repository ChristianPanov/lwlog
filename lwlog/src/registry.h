#pragma once

#include <functional>
#include <memory>

#include "fwd.h"
#include "interface/logger_interface.h"

namespace lwlog
{
	class registry
	{
	public:
		registry() = default;
		registry(const registry&) = delete;
		registry(registry&&) = delete;
		registry& operator=(const registry&) = delete;
		registry& operator=(registry&&) = delete;

	public:
		static registry& instance();
		static void init_default_logger();
		static const std::unique_ptr<interface::logger>& default_logger();

	public:
		void register_logger(logger_ptr logger);
		void set_automatic_registry(bool is_registry_automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		void apply_to_all(const std::function<void(logger_ptr)>& fn) const;

	public:
		bool is_registry_automatic() const;
		const std::unordered_map<std::string_view, logger_ptr>& loggers() const;
		logger_ptr get(std::string_view logger_name);

	private:
		bool m_is_registry_automatic{ true };
		std::unordered_map<std::string_view, logger_ptr> m_loggers;
		static inline std::unique_ptr<interface::logger> s_default_logger;
	};
}