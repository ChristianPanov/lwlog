#pragma once

#include "details/log_message.hpp"
#include "details/pattern/attribute.hpp"
#include "details/argument_format.hpp"

namespace lwlog::interface
{
	class logger
	{
	public:
		virtual ~logger() = default;

	public:
		virtual void sink_logs() = 0;

		virtual void set_pattern(std::string_view) = 0;
		virtual void add_attribute(std::string_view, details::attrib_value) = 0;
		virtual void add_attribute(std::string_view, details::attrib_value, details::attrib_callback_t) = 0;
		virtual void set_level_filter(level) = 0;

		template<typename... Args> void info(const details::log_message& log_msg, Args&&... args);
		template<typename... Args> void warning(const details::log_message& log_msg, Args&&... args);
		template<typename... Args> void error(const details::log_message& log_msg, Args&&... args);
		template<typename... Args> void critical(const details::log_message& log_msg, Args&&... args);
		template<typename... Args> void debug(const details::log_message& log_msg, Args&&... args);

		virtual std::string_view name() const = 0;

	protected:
		virtual void log(const details::log_message&, level, details::format_args_list) = 0;
		virtual void info_impl(const details::log_message&, details::format_args_list) = 0;
		virtual void warning_impl(const details::log_message&, details::format_args_list) = 0;
		virtual void error_impl(const details::log_message&, details::format_args_list) = 0;
		virtual void critical_impl(const details::log_message&, details::format_args_list) = 0;
		virtual void debug_impl(const details::log_message&, details::format_args_list) = 0;
	};
}

namespace lwlog
{
	using logger_ptr = interface::logger*;
}

#include "logger_interface_impl.hpp"