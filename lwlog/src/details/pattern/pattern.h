#pragma once

#include <memory>
#include <unordered_map>

#include "fwd.h"
#include "attribute.h"
#include "details/log_message.h"
#include "alignment_formatter.h"

namespace lwlog::details
{
	class pattern
	{
	public:
		std::string compile(const log_message& log_msg) const;
		void parse_alignment_specs();
		void request_flag_formatters();
		void set_pattern(std::string_view pattern);
		void add_attribute(const flag_pair& flags, attrib_value value);
		std::string& data();

	public:
		static void compile_colors(std::string& pattern);
		static void drop_color_flags(std::string& pattern);

	private:
		std::vector<std::string> parse_verbose_flags() const;
		std::vector<std::string> parse_short_flags() const;

	private:
		std::string m_pattern;
		std::vector<alignment_specification> m_alignment_specs;
		std::vector<std::shared_ptr<formatter>> m_formatters;
		std::unordered_map<flag_pair, attrib_value, attrib_hasher> m_custom_attributes;
	};
}