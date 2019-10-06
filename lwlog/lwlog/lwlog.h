#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "core.h"
#include "details/backtracer.h"

#include "sinks/sink.h"
#include "sinks/console_sink.h"
#include "sinks/file_sink.h"
#include "sinks/sink_factory.h"

namespace lwlog
{
	enum class level;
	
	template<typename SinkPolicy = sinks::console_sink>
	class LWLOG_API logger : public SinkPolicy
	{
	public:
		explicit logger(std::string_view name);
		virtual ~logger() = default;

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

	private:
		void log(std::string_view message, level log_level);
		void push_in_backtrace_buffer(std::string_view message);

	private:
		/*TODO: FIX IMMEDIATELY*/
		std::unordered_map<std::string, std::string> REALLY_STRANGE_BUG;
		/*TODO: FIX IMMEDIATELY*/

	private:
		std::string m_message;
		std::string m_logger_name;
		std::string m_level_string;

		details::backtracer m_tracer;
		std::unique_ptr<sinks::sink> m_sink;
	};
}
