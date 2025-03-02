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
	template<typename Config, typename BufferLimits>
	class pattern
	{
	public:
		const char* compile(const details::record<Config, BufferLimits>& record);
		void parse_alignment_flags();
		void request_flag_formatters();
		void process_color_flags(bool use_color);
		void cache_pattern();
		void reset_pattern();

	public:
		void set_pattern(std::string_view pattern);
		void add_attribute(std::string_view flag, attrib_value value);
		void add_attribute(std::string_view flag, attrib_value value, const attrib_callback_t& fn);

	private:
		std::unique_ptr<formatter<Config, BufferLimits>> flag_to_formatter(std::string_view flag) const;
		std::vector<std::string_view> parse_verbose_flags();
		std::vector<std::string_view> parse_short_flags();

	private:
		details::memory_buffer<BufferLimits::pattern> m_pattern_buffer;

		char m_cached_pattern_buffer[BufferLimits::pattern];
		char m_padding_buffer[BufferLimits::padding];
		char m_conv_buffer[BufferLimits::conversion];

	private:
		std::vector<alignment_info> m_alignment_flags_info;
		std::vector<std::unique_ptr<formatter<Config, BufferLimits>>> m_formatters;
		std::vector<attribute> m_attributes;
	};
}

#include "pattern_impl.h"