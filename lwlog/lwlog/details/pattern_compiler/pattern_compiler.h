#pragma once

#include <vector>
#include <memory>

#include "details/log_message.h"

namespace lwlog::details
{
	struct formatter
	{
		virtual ~formatter() = default;
		virtual void format(log_message&) = 0;
	};

	class pattern_compiler
	{
	private:
		using formatter_storage = std::vector<std::shared_ptr<formatter>>;

	public:
		pattern_compiler() = default;
		pattern_compiler(const log_message& message);
		std::string compile();
		static void compile_colors(std::string& pattern);

	public:
		static void format_attribute(log_message& message, std::string_view attribute, std::string_view value);
		static void format_attribute(log_message& message, std::string_view verbose,
			std::string_view shortened, std::string_view value);

	private:
		bool contains(std::string_view attribute);
		bool contains(std::string_view verbose, std::string_view shortened);
		formatter_storage handle_logger_formatters();
		formatter_storage handle_datetime_formatters();

	private:
		log_message m_message;
	};
}