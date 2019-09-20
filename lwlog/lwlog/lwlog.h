#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "core.h"

namespace lwlog
{
	enum class level;

	class LWLOG_API logger
	{
	public:
		explicit logger(std::string_view name);
		virtual ~logger() = default;

		void set_level_visibility(level logLevel);
		void set_pattern(std::string_view pattern);

		void backtrace(std::size_t buffer_size);
		void set_backtrace_stamp(std::string_view stamp);
		void display_backtrace();
		void delete_backtrace();

		void info(std::string_view message);
		void warning(std::string_view message);
		void error(std::string_view message);
		void critical(std::string_view message);
		void debug(std::string_view message);

		inline std::string get_name() const;
		inline std::string get_pattern() const;

	private:
		void log(std::string_view message, level log_level);
		void push_in_backtrace_buffer(std::string_view message);

	private:
		std::vector<std::string> m_backtrace_buffer;
		/*TODO: FIX IMMEDIATELY*/
		std::unordered_map<std::string, std::string> REALLY_STRANGE_BUG;
		/*TODO: FIX IMMEDIATELY*/

	private:
		std::string m_message;
		std::string m_logger_name;
		std::string m_pattern;
		std::string m_level_string;
		level m_level;
		std::string m_backtrace_stamp;
		int m_backtrace_messages;
		bool m_is_backtrace_enabled;
	};
}
