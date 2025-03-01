#pragma once

#include "policy/log_policy.h"
#include "details/log_message.h"

namespace lwlog
{
	template<typename Config, typename BufferLimits, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename, typename, typename> typename... Sinks>
	class logger
	{
	public:
		template<typename... SinkParams>
		logger(std::string_view name, SinkParams&&... params);
		template<typename Iterator, typename... SinkParams>
		logger(std::string_view name, Iterator begin, Iterator end, SinkParams&&... params);
		template<typename... SinkParams>
		logger(std::string_view name, sink_list<Config, BufferLimits> sink_list, SinkParams&&... params);
		template<typename... SinkParams>
		logger(std::string_view name, sink_ptr<Config, BufferLimits> sink, SinkParams&&... params);

	public:
		void add_sink(sink_ptr<Config, BufferLimits> sink);
		void remove_sink(sink_ptr<Config, BufferLimits> sink);

		void set_level_filter(level log_level);
		void set_pattern(std::string_view pattern);
		void add_attribute(std::string_view flag, details::attrib_value value);
		void add_attribute(std::string_view flag, details::attrib_value value, const details::attrib_callback_t& fn);

		void set_topic_separator(std::string_view separator);
		void start_topic(std::string_view topic);
		void end_topic();

		std::string_view name() const;
		std::vector<sink_ptr<Config, BufferLimits>>& sinks();

	public:
		template<typename... Args> void info(const details::log_message& log_msg, Args&&... args);
		template<typename... Args> void warning(const details::log_message& log_msg, Args&&... args);
		template<typename... Args> void error(const details::log_message& log_msg, Args&&... args);
		template<typename... Args> void critical(const details::log_message& log_msg, Args&&... args);
		template<typename... Args> void debug(const details::log_message& log_msg, Args&&... args);
	
	private:
		template<typename... Args> 
		void log(const details::log_message& log_msg, level log_level, Args&&... args);

	private:
		std::string_view m_name;
		typename LogExecutionPolicy::template backend<Config, BufferLimits, 
			typename ThreadingPolicy::concurrency_model_policy> m_backend;
	};
}

#include "logger_impl.h"
