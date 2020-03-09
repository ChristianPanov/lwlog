#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "core.h"
#include "logger_interface.h"
#include "sinks/sink.h"
#include "sinks/console_sink.h"
#include "sinks/file_sink.h"
#include "details/backtracer.h"

namespace lwlog
{
	template<typename ... SinkPolicyArgs>
	class LWLOG_API logger : public logger_interface, public SinkPolicyArgs...
	{
	public:
		explicit logger(std::string_view name);

		template<typename Iterator>
		logger(std::string_view name, Iterator begin, Iterator end)
			: logger(name)
		{
			m_sink_buffer = { begin, end };
		}

		logger(std::string_view name, sinks::sink_ptr sink);
		logger(std::string_view name, std::initializer_list<sinks::sink_ptr> sink_list);
		logger(const logger& other);
		logger(logger&& other) noexcept;
		logger& operator=(logger& other);
		logger& operator=(logger&& other) noexcept;
		virtual ~logger() = default;

		void set_pattern(std::string_view pattern) override;
		void set_level_visibility(std::initializer_list<sink_level> level_list) override;

		void info(std::string_view message) override;
		void warning(std::string_view message) override;
		void error(std::string_view message) override;
		void critical(std::string_view message) override;
		void debug(std::string_view message) override;

		void backtrace(std::size_t buffer_size) override;
		void disable_backtrace() override;
		void set_backtrace_stamp(std::string_view stamp) override;
		void display_backtrace() override;
		void delete_backtrace() override;

		inline std::string name() const override;
		inline std::vector<sinks::sink_ptr> sinks() const override;

	private:
		void log(std::string_view message, sink_level level) override;

	private:
		std::string m_name;
		std::string m_message;
		std::string m_level_string;

		std::vector<sinks::sink_ptr> m_sink_buffer;
		details::backtracer m_tracer;
	};
}
