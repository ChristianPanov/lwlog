#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "attribute.h"
#include "formatter.h"
#include "alignment_formatter.h"
#include "details/record.h"

#include "details/memory_buffer.h"

namespace lwlog::details
{
	class pattern
	{
	public:
		std::string compile(const details::record_base& record);
		void parse_alignment_flags();
		void request_flag_formatters();
		void process_color_flags(bool use_color);
		void save_pattern_state();
		void reset_pattern();

	public:
		void set_pattern(std::string_view pattern);
		void add_attribute(std::string_view flag, attrib_value value);
		void add_attribute(std::string_view flag, attrib_value value, const attrib_callback_t& fn);

	private:
		std::vector<std::string_view> parse_verbose_flags() const;
		std::vector<std::string_view> parse_short_flags() const;

	private:
		char m_chached_pattern[128];
		details::memory_buffer<> m_pattern_buffer;

		std::vector<alignment_info> m_alignment_flags_info;
		std::vector<std::shared_ptr<formatter>> m_formatters;
		std::vector<attribute> m_attributes;
	};
}