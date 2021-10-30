#pragma once

#include <unordered_map>

#include "attribute.h"
#include "details/log_message.h"
#include "alignment_formatter.h"

namespace lwlog::details
{
	struct formatter
	{
		virtual ~formatter() = default;
		virtual void format(std::string&, const log_message&) = 0;
	};

	class pattern
	{
	public:
		std::string compile(const log_message& log_msg);
		void handle_alignment_specs();
		void handle_flag_formatters();
		void set_pattern(std::string_view pattern);
		void add_attribute(flag_pair flags, attrib_value value);
		std::string& data();

	public:
		static void compile_colors(std::string& pattern);
		static void drop_color_flags(std::string& pattern);
		static void format_attribute(std::string& pattern, flag_pair flags, std::string_view value);

	private:
		std::vector<std::string> parse_verbose_flags();
		std::vector<std::string> parse_short_flags();

	private:
		std::string m_pattern;
		std::vector<alignment_specification> m_alignment_specs;
		std::vector<std::shared_ptr<formatter>> m_formatters;
		std::unordered_map<flag_pair, attrib_value, attrib_hasher> m_custom_attributes;
	};
}