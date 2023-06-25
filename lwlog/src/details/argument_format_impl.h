#pragma once

namespace lwlog::details
{
	static std::string format_arguments(std::string_view format, format_args_list args)
	{
		std::string result;
		std::size_t pos{ 0 };

		for (const auto& arg : args)
		{
			const std::size_t placeholder_pos{ format.find("{}", pos) };

			result.append(format.substr(pos, placeholder_pos - pos));
			result.append(arg);

			pos = placeholder_pos + 2;
		}

		result.append(format.substr(pos));
		return result;
	}

	template<typename T>
	static const char* to_raw_string(T arg)
	{
		return std::to_string(arg).data();
	}

	template<> static const char* to_raw_string<const char*>(const char* arg) { return arg; }
	template<> static const char* to_raw_string<std::string>(std::string arg) { return arg.c_str(); }
	template<> static const char* to_raw_string<std::string_view>(std::string_view arg) { return arg.data(); }
}