#pragma once

#include "flag_data.h"
#include "level.h"

namespace lwlog::details
{
	struct logger_name_formatter : public formatter
	{
		virtual void format(std::string& pattern, log_message& log_msg) override
		{
			pattern::format_attribute(
				pattern,
				flag::logger_name,
				log_msg.logger_name
			);
		}
	};

	struct level_formatter : public formatter
	{
		virtual void format(std::string& pattern, log_message& log_msg) override
		{
			auto level = lwlog::level_details::to_string(log_msg.level);
			pattern::format_attribute(
				pattern,
				flag::level,
				level
			);
		}
	};

	struct level_color_formatter : public formatter
	{
		virtual void format(std::string& pattern, log_message& log_msg) override
		{
			pattern::format_attribute(
				pattern,
				flag::level_color,
				lwlog::level_details::color_value(log_msg.level)
			);
		}
	};

	struct message_formatter : public formatter
	{
		virtual void format(std::string& pattern, log_message& log_msg) override
		{
			pattern::format_attribute(
				pattern,
				flag::message,
				log_msg.message
			);
		}
	};

	struct thread_id_formatter : public formatter
	{
		virtual void format(std::string& pattern, log_message& log_msg) override
		{
			pattern::format_attribute(
				pattern,
				flag::thread_id,
				std::to_string(log_msg.thread_id)
			);
		}
	};
}