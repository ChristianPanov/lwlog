#pragma once

#include <vector>

#include "details/log_message.h"

namespace lwlog::details
{
	struct formatter
	{
		virtual ~formatter() = default;
		virtual void format(std::string&, log_message&) = 0;
	};

	class pattern
	{
	public:
		std::string compile(log_message& log_msg);
		void handle_flag_formatters();
		void set_pattern(std::string_view pattern);
		std::string& data();

	public:
		static void compile_colors(std::string& pattern);
		static void format_attribute(std::string& pattern, flag::flag_pair flags, std::string_view value);

	private:
		bool contains(flag::flag_pair flags);
		std::vector<std::string> verbose_flags();
		std::vector<std::string> short_flags();

	private:
		std::string m_pattern;
		std::vector<std::shared_ptr<formatter>> m_formatters;
	};
}