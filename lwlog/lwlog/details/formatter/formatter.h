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
		using key_hasher = formatter_primitives::attribute_key_hasher;
		using pattern_map = std::unordered_map<formatter_primitives::attribute_key, std::string, key_hasher>;

	public:
		static std::string format(std::string pattern);
		static std::string format_color(std::string pattern);
		static void insert_pattern_data(std::initializer_list<primitives::attribute_t> attributes);
	};
}