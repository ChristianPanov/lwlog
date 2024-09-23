#pragma once

#include "policy/log_policy.h"
#include "interface/logger_interface.h"

#include "policy/topic_policy.h"

namespace lwlog
{
	template<typename Config, typename LogExecutionPolicy, typename FlushPolicy,
		typename ThreadingPolicy, template<typename, typename> typename... Sinks>
	class logger : public interface::logger
	{
	public:
		template<typename... SinkParams>
		logger(std::string_view name, SinkParams&&... params);
		template<typename Iterator, typename... SinkParams>
		logger(std::string_view name, Iterator begin, Iterator end, SinkParams&&... params);
		template<typename... SinkParams>
		logger(std::string_view name, sink_list sink_list, SinkParams&&... params);
		template<typename... SinkParams>
		logger(std::string_view name, sink_ptr sink, SinkParams&&... params);

	public:
		void add_sink(sink_ptr sink);
		void remove_sink(sink_ptr sink);

		void set_pattern(std::string_view pattern) override;
		void add_attribute(std::string_view flag, details::attrib_value value) override;
		void add_attribute(std::string_view flag, details::attrib_value value, details::attrib_callback_t fn) override;
		void set_level_filter(level log_level) override;

		std::string_view name() const override;
		std::vector<sink_ptr>& sinks();

		void start_topic(std::string_view topic) { topic_registry<typename Config::topic_t>::start_topic(topic, m_topics); }
		void end_topic() { topic_registry<typename Config::topic_t>::end_topic(m_topics); }

	private:
		void log(const details::log_message& log_msg, level log_level, details::format_args_list args) override;
		void info_impl(const details::log_message& log_msg, details::format_args_list args) override;
		void warning_impl(const details::log_message& log_msg, details::format_args_list args) override;
		void error_impl(const details::log_message& log_msg, details::format_args_list args) override;
		void critical_impl(const details::log_message& log_msg, details::format_args_list args) override;
		void debug_impl(const details::log_message& log_msg, details::format_args_list args) override;

	private:
		std::string_view m_name;
		typename topic_registry<typename Config::topic_t>::container m_topics;
		typename LogExecutionPolicy::template backend<
			typename ThreadingPolicy::concurrency_model_policy> m_backend;
	};
}

#include "logger_impl.h"
