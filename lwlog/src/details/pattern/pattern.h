#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "fwd.h"
#include "attribute.h"
#include "details/record.h"
#include "alignment_formatter.h"

namespace lwlog::details
{
	class pattern
	{
	public:
		std::string compile(const record& record) const;
		void parse_alignment_flags();
		void request_flag_formatters();
		void process_color_flags(bool use_color);
		void set_pattern(std::string_view pattern);
		void add_attribute(std::string_view flag, attrib_value value);
		void add_attribute(std::string_view flag, attrib_value value, attrib_callback_t fn);

	private:
		std::vector<std::string_view> parse_verbose_flags() const;
		std::vector<std::string_view> parse_short_flags() const;

	private:
		std::string m_pattern;
		std::vector<alignment_info> m_alignment_flags_info;
		std::vector<std::shared_ptr<formatter>> m_formatters;
		std::vector<attribute> m_attributes;
	};
}