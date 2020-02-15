#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "core.h"
#include "sinks/sink.h"
#include "sinks/console_sink.h"
#include "sinks/file_sink.h"
#include "details/backtracer.h"

namespace lwlog
{
	template<typename ... SinkPolicyArgs>
	class LWLOG_API logger : public SinkPolicyArgs...
	{
	public:
		explicit logger(std::string_view name);
		virtual ~logger() = default;

		void set_pattern(std::string_view pattern);
		void set_level_visibility(std::initializer_list<sink_level> level_list);

		void info(std::string_view message);
		void warning(std::string_view message);
		void error(std::string_view message);
		void critical(std::string_view message);
		void debug(std::string_view message);

		void backtrace(std::size_t buffer_size);
		void disable_backtrace();
		void set_backtrace_stamp(std::string_view stamp);
		void display_backtrace();
		void delete_backtrace();

		inline std::string name() const;
		inline std::vector<std::shared_ptr<sinks::sink>> sinks() const;

	private:
		void log(std::string_view message, sink_level level);

	private:
		std::string m_name;
		std::string m_message;
		std::string m_level_string;

		details::backtracer m_tracer;
		std::vector<std::shared_ptr<sinks::sink>> m_sink_buffer;
	};
}
