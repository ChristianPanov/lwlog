#pragma once

#include <string>
#include <unordered_map>

#include "formatter_primitives.h"
#include "fwd.h"

namespace lwlog::details
{
	class formatter
	{
	private:
		using key_hasher	= formatter_primitives::attribute_key_hasher;
		using pattern_map	= std::unordered_map<formatter_primitives::attribute_key, std::string, key_hasher>;
		using color_map		= std::unordered_map<std::string_view, std::string_view>;

	public:
		static std::string format(std::string pattern, bool should_color);
		static void insert_pattern_data(std::initializer_list<primitives::attribute_t> attributes);

	private:
		static pattern_map m_datetime_data;
		static color_map m_color_data;
	};
}