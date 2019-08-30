#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <tuple>

#include "details.h"
#include "core.h"

namespace lwlog
{
	class LWLOG_API formatter
	{
	private:
		static std::unordered_map<details::Key_Value, std::string> m_patternData;
		static std::vector<details::Key_Value> m_inserted_patternData_keys;

	public:
		formatter() = delete;
		formatter(const formatter&) = delete;
		formatter(formatter&&) = delete;
		formatter& operator=(const formatter&) = delete;
		formatter& operator=(formatter&&) = delete;

		virtual ~formatter() = default;
		static void insert_pattern_data(details::Key_Value key, std::string value);
		static std::string format(std::string pattern);
	};
}
