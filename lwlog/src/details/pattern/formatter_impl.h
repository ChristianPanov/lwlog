#pragma once

#include <cstring>

namespace lwlog::details
{
	template<typename T>
	void formatter::format_attribute(std::string& pattern, const flag_pair& flags, T value)
	{
		const std::string_view str_value = [&value]() {
			if constexpr (std::is_arithmetic_v<T>)					return std::to_string(value);
			else if constexpr (std::is_same_v<T, std::string>)		return value.data();
			else if constexpr (std::is_same_v<T, std::string_view>)	return value;
			else if constexpr (std::is_same_v<T, const char*>)		return value;
			else													return "";
		}();

		const auto& [verbose, shortened] = flags;
		while (std::strstr(pattern.data(), verbose.data()))
			pattern.replace(pattern.find(verbose), verbose.length(), str_value);

		while (std::strstr(pattern.data(), shortened.data()))
			pattern.replace(pattern.find(shortened), shortened.length(), str_value);
	}

	template<typename T>
	void formatter::format_attribute(std::string& pattern, std::string_view flag, T value)
	{
		const std::string_view str_value = [&value]() {
			if constexpr (std::is_arithmetic_v<T>)					return std::to_string(value);
			else if constexpr (std::is_same_v<T, std::string>)		return value.data();
			else if constexpr (std::is_same_v<T, std::string_view>)	return value;
			else if constexpr (std::is_same_v<T, const char*>)		return value;
			else													return "";
		}();

		while (std::strstr(pattern.data(), flag.data()))
			pattern.replace(pattern.find(flag), flag.length(), str_value);
	}
}