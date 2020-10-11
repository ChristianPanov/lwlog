#pragma once

#include <string>
#include <vector>

#include "interface/logger_interface.h"
#include "details/log_message.h"
#include "sinks/sink.h"
#include "sinks/sink_level.h"
#include "details/formatter.h"

namespace lwlog
{
	template<typename ... SinkPolicy>
	class logger : public interface::logger, public SinkPolicy...
	{
	public:
		template<typename ... SinkParams>
		logger(std::string_view name, SinkParams&&... params);
		template<typename Iterator, typename ... SinkParams>
		logger(std::string_view name, Iterator begin, Iterator end, SinkParams&&... params);
		template<typename ... SinkParams>
		logger(std::string_view name, sinks::sink_list sink_list, SinkParams&&... params);
		template<typename ... SinkParams>
		logger(std::string_view name, sinks::sink_ptr sink, SinkParams&&... params);

	public:
		void add_sink(sinks::sink_ptr sink) override;
		void remove_sink(sinks::sink_ptr sink) override;

		void set_pattern(std::string_view pattern) override;
		void add_pattern_attribute(details::pattern_attribute attribute) override;
		void set_level_filter(std::initializer_list<sink_level> level_list) override;

		void info(std::string_view message) override;
		void warning(std::string_view message) override;
		void error(std::string_view message) override;
		void critical(std::string_view message) override;
		void debug(std::string_view message) override;

		std::string name() const override;
		std::vector<sinks::sink_ptr>& sinks() override;

	private:
		void log(std::string_view message, sink_level level) override;

	private:
		std::string m_name;
		log_message m_message;
		std::vector<sinks::sink_ptr> m_sink_buffer;
	};
}

#include "logger_impl.h"
