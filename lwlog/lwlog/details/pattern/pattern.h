#pragma once

#include <vector>
#include <memory>

#include "details/log_message.h"
#include "fwd.h"

namespace lwlog::details
{
	struct formatter
	{
		virtual ~formatter() = default;
		virtual void format(log_message&) = 0;
	};

	class pattern
	{
	private:
		using formatter_storage = std::vector<std::shared_ptr<formatter>>;

	public:
		pattern() = default;
		pattern(const log_message& message);
		std::string compile();
		static void compile_colors(std::string& pattern);

	public:
		static void format_attribute(log_message& message, flag::flag_pair flags, std::string_view value);

	private:
		bool contains(flag::flag_pair flags);
		formatter_storage handle_logger_formatters();
		formatter_storage handle_datetime_formatters();

	private:
		log_message m_message;
	};
}