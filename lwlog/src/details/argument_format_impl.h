#pragma once

namespace lwlog::details
{
	static std::string format_args_impl(std::string_view format, format_args_list args)
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

	static std::string format_args(std::string_view format, format_args_list args)
	{
		#if __cplusplus < 202002L
			#ifdef FMT_VERSION
				return fmt::format(format, args);
			#else
				return format_args_impl(format, args);
			#endif
		#else
			return std::format(format, args);
		#endif
	}

	template<typename T>
	static const char* to_raw_string(T arg)
	{
		return std::to_string(arg).data();
	}

	template<> const char* to_raw_string<const char*>(const char* arg) { return arg; }
	template<> const char* to_raw_string<std::string>(const std::string& arg) { return arg.c_str(); }
	template<> const char* to_raw_string<std::string_view>(std::string_view arg) { return arg.data(); }
}