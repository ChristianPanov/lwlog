#pragma once

#include <unordered_map>

namespace lwlog::details
{
	class color_compiler
	{
	public:
		static void compile(std::string& str);
		static void drop_flags(std::string& str);

	private:
		static void compile_rgb(std::string& str);
		static void compile_predefined(std::string& str);
		static void terminate_scopes(std::string& str);
		static std::vector<std::string> parse_rgb_flags(const std::string& str);
		static std::string_view to_ansiec(const std::string& flag);

	private:
		static std::unordered_map<std::string_view, const char*> m_data;
	};
}