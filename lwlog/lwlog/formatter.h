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
		static std::string format(std::string pattern);
		static void insert_pattern_data(details::duplex<std::string, std::string> duplex_key, std::string_view value);

	public:
		static std::unordered_map<details::duplex<std::string, std::string>, std::string> m_pattern_data;
		static std::vector<details::duplex<std::string, std::string>> m_inserted_pattern_data_keys;
	};
}
