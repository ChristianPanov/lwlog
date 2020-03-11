#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "../core.h"
#include "duplex.h"

namespace lwlog::details
{
	class LWLOG_API formatter
	{
	public:
		static std::string format(std::string pattern, bool should_color);
		static void insert_pattern_data(std::initializer_list<duplex<duplex<std::string, std::string>, std::string>> pattern_data);

	public:
		static std::unordered_map<duplex<std::string, std::string>, std::string> m_pattern_data;
		static std::unordered_map<std::string, std::string> m_color_data;
	};
}
