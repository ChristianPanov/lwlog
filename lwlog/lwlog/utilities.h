#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <regex>

#include "details.h"

namespace lwlog 
{
	template<typename... Args>
	void print(std::string format_str, Args&& ... args) 
	{
		std::regex reg("(\\{\\d+\\})");

		std::vector<std::string> format_string_tokens = details::populate_with_regex_matches_from_str(reg, format_str);
		std::vector<int> format_numeric_tokens;

		std::vector<std::string> variadic_arguments;

		(details::populate_vec_with_variadic_params(variadic_arguments, std::forward<Args>(args)), ...);

		details::remove_duplicates_in_vec(variadic_arguments);

		details::string_to_numeric_vec(format_string_tokens, format_numeric_tokens, "{}");

		for (int i = 0; i < format_string_tokens.size(); ++i) 
		{
			if (i < variadic_arguments.size()) 
			{
				details::replace_in_string(format_str, format_string_tokens[i], 
					variadic_arguments[format_numeric_tokens[i]]);
			}
			else 
			{
				break;
			}
		}

		std::cout << format_str;
	}
}