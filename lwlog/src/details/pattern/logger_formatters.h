#pragma once

#include "formatter.h"
#include "flag_data.h"
#include "level.h"

namespace lwlog::details
{
	struct logger_name_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::logger_name,
				log_msg.logger_name
			);
		}
	};

	struct level_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::level,
				lwlog::level_details::to_string(log_msg.level)
			);
		}
	};

	struct level_color_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::level_color,
				lwlog::level_details::color_value(log_msg.level)
			);
		}
	};

	struct message_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::message,
				log_msg.message
			);
		}
	};

	struct thread_id_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::thread_id,
				std::to_string(log_msg.thread_id)
			);
		}
	};

	struct line_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::line,
				std::to_string(log_msg.meta.line())
			);
		}
	};

	struct file_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::file,
				log_msg.meta.file_name()
			);
		}
	};

	struct function_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::function,
				log_msg.meta.function_name()
			);
		}
	};
}