#pragma once

#include <iostream>
#include <string>
#include <cctype>

#include "core.h"
#include "detail.h"
#include "datetime.h"
#include "registry.h"

namespace lwlog
{
	enum class log_level
	{
		all =		(1 << 0),
		info =		(1 << 1),
		warning =	(1 << 2),
		error =		(1 << 3),
		critical =	(1 << 4),
		debug =		(1 << 5),
		none =		(1 << 6)
	};

	static log_level operator |(log_level lhs, log_level rhs)
	{
		return static_cast<log_level> (
			static_cast<std::underlying_type<log_level>::type>(lhs) 
			| static_cast<std::underlying_type<log_level>::type>(rhs)
			);
	}

	static log_level operator &(log_level lhs, log_level rhs)
	{
		return static_cast<log_level> (
			static_cast<std::underlying_type<log_level>::type>(lhs) 
			& static_cast<std::underlying_type<log_level>::type>(rhs)
			);
	}

	class LWLOG logger
	{
	private:
		std::string m_message;
		std::string m_loggerName;
		std::string m_pattern;
		std::string m_logLevel;
		log_level m_logLevel_visibility = log_level::all;

		std::unordered_map<std::string, std::string> m_patterns_data;

	private:
		void print_formatted(const std::string& message, std::string pattern);

	public:
		explicit logger(const std::string& name);
		~logger();

		void set_name(const std::string& loggerName);
		void set_logLevel_visibility(log_level logLevel);
		void set_pattern(const std::string& pattern);

		void info(const std::string& message);
		void warning(const std::string& message);
		void error(const std::string& message);
		void critical(const std::string& message);
		void debug(const std::string& message);

		inline std::string get_name() const { return m_loggerName; }
		inline std::string get_logLevel() const { return m_logLevel; }
	};

	template<typename... Args>
	void print(std::string format_str, Args&&... args)
	{
		std::vector<std::string> format_string_tokens_vec;
		std::vector<int> format_numeric_tokens_vec;

		std::vector<std::string> variadic_arguments_vec;

		std::regex reg("(\\{\\d\\})");

		(detail::populate_vec_with_variadic_params(variadic_arguments_vec, std::forward<Args>(args)), ...);
		detail::populate_vec_with_regex_matches_from_str(format_string_tokens_vec, reg, format_str);

		detail::remove_duplicates_in_vec(variadic_arguments_vec);

		detail::string_to_numeric_vec(format_string_tokens_vec, format_numeric_tokens_vec, "{}");

		for (int i = 0; i < format_string_tokens_vec.size(); ++i)
		{
			detail::replace_in_string(format_str, format_string_tokens_vec[i], variadic_arguments_vec[format_numeric_tokens_vec[i]]);
		}

		std::cout << format_str;
	}
}
