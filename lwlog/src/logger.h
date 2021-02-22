#pragma once

#include "policy/log_policy.h"
#include "policy/sink_storage_policy.h"
#include "interface/logger_interface.h"

namespace lwlog
{
	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	class logger : public interface::logger, private LogPolicy, public Sinks<ThreadingPolicy>...
	{
	private:
		using Storage = typename StoragePolicy<Sinks<ThreadingPolicy>...>::storage;

	public:
		template<typename... SinkParams>
		logger(std::string_view name, SinkParams&&... params);
		template<typename Iterator, typename... SinkParams>
		logger(std::string_view name, Iterator begin, Iterator end, SinkParams&&... params);
		template<typename... SinkParams>
		logger(std::string_view name, primitives::sink_list sink_list, SinkParams&&... params);
		template<typename... SinkParams>
		logger(std::string_view name, primitives::sink_ptr sink, SinkParams&&... params);

	public:
		void add_sink(primitives::sink_ptr sink);
		void remove_sink(primitives::sink_ptr sink);
		void sink_logs() override;

		void set_pattern(std::string_view pattern) override;
		void add_attribute(details::flag_pair flags, details::attrib_value value) override;
		void set_level_filter(level t_level) override;

		void info(std::string_view message) override;
		void warning(std::string_view message) override;
		void error(std::string_view message) override;
		void critical(std::string_view message) override;
		void debug(std::string_view message) override;

		std::string name() const override;
		Storage& sinks();

	private:
		void log(std::string_view message, level t_level) override;

	private:
		std::string m_name;
		Storage m_sink_storage;
	};
}

#include "logger_impl.h"
