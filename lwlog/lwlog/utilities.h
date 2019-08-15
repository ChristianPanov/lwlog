#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <regex>

#include "detail.h"

namespace lwlog
{
	template<typename... Args>
	void print(std::string format_str, Args&& ... args)
	{
		std::vector<std::string> format_string_tokens;
		std::vector<int> format_numeric_tokens;

		std::vector<std::string> variadic_arguments;

		std::regex reg("(\\{\\d+\\})");

		(detail::populate_vec_with_variadic_params(variadic_arguments, std::forward<Args>(args)), ...);
		detail::populate_vec_with_regex_matches_from_str(format_string_tokens, reg, format_str);

		detail::remove_duplicates_in_vec(variadic_arguments);

		detail::string_to_numeric_vec(format_string_tokens, format_numeric_tokens, "{}");

		for (int i = 0; i < format_string_tokens.size(); ++i)
		{
			if (i < variadic_arguments.size())
			{
				detail::replace_in_string(format_str, format_string_tokens[i],
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