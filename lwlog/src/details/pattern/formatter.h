#pragma once

namespace lwlog::details
{
	struct formatter
	{
		virtual ~formatter() = default;
		virtual void format(std::string&, const log_message&) = 0;

		static void format_attribute(std::string& pattern, flag_pair flags, std::string_view value)
		{
			const auto& [verbose, shortened] = flags;
			while (std::strstr(pattern.data(), verbose.data()))
				pattern.replace(pattern.find(verbose), verbose.length(), value);

			while (std::strstr(pattern.data(), shortened.data()))
				pattern.replace(pattern.find(shortened), shortened.length(), value);
		}
	};
}