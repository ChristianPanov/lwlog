#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "core.h"
#include "details/duplex.h"

namespace lwlog
{
	class LWLOG_API formatter
	{
	public:
		virtual ~formatter() = default;
		static std::string format(std::string pattern, bool should_color);
		static void insert_pattern_data(std::initializer_list<details::duplex<details::duplex<std::string, std::string>, std::string>> pattern_data);

	public:
		static std::unordered_map<details::duplex<std::string, std::string>, std::string> m_pattern_data;
		static std::unordered_map<std::string, std::string> m_color_data;
	};
}
