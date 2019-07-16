#pragma once

#include <iostream>
#include <vector>
#include <regex>

#include "detail.h"

namespace lwlog
{
	template<typename... Args>
	void print(std::string format_str, Args&& ... args)
	{
		std::vector<std::string> format_string_tokens_vec;
		std::vector<int> format_numeric_tokens_vec;

		std::vector<std::string> variadic_arguments_vec;

		std::regex reg("(\\{\\d+\\})");

		(detail::populate_vec_with_variadic_params(variadic_arguments_vec, std::forward<Args>(args)), ...);
		detail::populate_vec_with_regex_matches_from_str(format_string_tokens_vec, reg, format_str);

		detail::remove_duplicates_in_vec(variadic_arguments_vec);

		detail::string_to_numeric_vec(format_string_tokens_vec, format_numeric_tokens_vec, "{}");

		for (int i = 0; i < format_string_tokens_vec.size(); ++i)
		{
			if (i < variadic_arguments_vec.size())
			{
				detail::replace_in_string(format_str, format_string_tokens_vec[i],
					variadic_arguments_vec[format_numeric_tokens_vec[i]]);
			}
			else
			{
				break;
			}
		}

		std::cout << format_str;
	}
}