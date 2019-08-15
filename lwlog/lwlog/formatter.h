#pragma once

#include <string>
#include <unordered_map>
#include <regex>

#include "core.h"
#include "details.h"
#include "datetime.h"

namespace lwlog
{
	class LWLOG_API formatter
	{
	private:
		static std::unordered_map<std::string, std::string> m_patternData;
		static inline std::regex pattern_regex{ "(\\%\\w{1})" };

	public:
		virtual ~formatter() = default;
		static void update_pattern_data(std::string_view key, std::string_view value);
		static std::string format(std::string_view message, std::string pattern);
	};
}
