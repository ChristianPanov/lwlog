#pragma once

namespace lwlog::details
{
	struct logger_name_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{name}", "%n",
				log_msg.logger_name
			);
		}
	};

	struct level_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			auto level = lwlog::level_details::to_string(log_msg.level);
			pattern_compiler::format_attribute(
				log_msg,
				"{level}", "%l",
				level
			);
		}
	};

	struct level_color_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"^level^",
				lwlog::level_details::color_value(log_msg.level)
			);
		}
	};

	struct message_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{message}", "%v",
				log_msg.message
			);
		}
	};

	struct thread_id_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{thread}", "%t",
				std::to_string(log_msg.thread_id)
			);
		}
	};
}