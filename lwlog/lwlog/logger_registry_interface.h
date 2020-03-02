#pragma once

#include <memory>

#include "core.h"
#include "logger_interface.h"

namespace lwlog
{
	namespace sinks { class sink; }
	class LWLOG_API  logger_registry_interface : public logger_interface
	{
	public:
		virtual void info(std::string_view) = 0;
		virtual void warning(std::string_view) = 0;
		virtual void error(std::string_view) = 0;
		virtual void critical(std::string_view) = 0;
		virtual void debug(std::string_view) = 0;

		virtual void backtrace(std::size_t) = 0;
		virtual void disable_backtrace() = 0;
		virtual void set_backtrace_stamp(std::string_view) = 0;
		virtual void display_backtrace() = 0;
		virtual void delete_backtrace() = 0;

		virtual inline std::string name() const = 0;
		virtual inline std::vector<std::shared_ptr<sinks::sink>> sinks() const = 0;
	};
}