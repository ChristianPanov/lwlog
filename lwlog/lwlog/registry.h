#pragma once

#include <string>
#include <map>
#include <memory>
#include <variant>

#include "core.h"
#include "logger.h"
#include "details/singleton.h"

#include <variant>
#include <algorithm>
#include <functional>

namespace lwlog
{
	using MyTypes = std::variant<
		logger<sinks::console_sink>*,
		logger<sinks::file_sink>*,
		logger<sinks::console_sink, sinks::file_sink>*,
		logger<sinks::file_sink, sinks::console_sink>*
	>;

	class LWLOG_API registry : public singleton
	{
	public:
		static registry& instance();
		void register_logger(std::string_view name, MyTypes logger);
		void set_automatic_registry(bool automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		inline bool is_registry_automatic();

		std::shared_ptr<logger<sinks::console_sink>> default_logger();

		auto get(std::string_view name)
		{
		}

	private:
		registry();

	private:
		std::map<std::string, MyTypes> m_loggers;
		bool m_automatic_registry{true};
		//std::shared_ptr<logger<sinks::console_sink>> m_default_logger;
	};
}
