#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

#include "core.h"

namespace lwlog
{
	class LWLOG_API formatter
	{
	private:
		static std::regex m_pattern_regex;
		static std::vector<std::string> m_inserted_patternData_keys;
		static std::unordered_map<std::string, std::string> m_patternData;

	public:
		formatter() = delete;
		formatter(const formatter&) = delete;
		formatter(formatter&&) = delete;
		formatter& operator=(const formatter&) = delete;
		formatter& operator=(formatter&&) = delete;

		virtual ~formatter() = default;
		static void insert_pattern_data(std::string_view key, std::string_view value);
		static std::string format(std::string_view message, std::string pattern, std::regex reg = m_pattern_regex);
	};
}
