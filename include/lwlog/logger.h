#pragma once

#include <string>
#include <vector>

#include "lwlog/primitives.h"
#include "lwlog/interface/logger_interface.h"
#include "lwlog/sinks/sink.h"
#include "lwlog/policy/log_policy.h"
#include "lwlog/policy/sink_storage_policy.h"
#include "lwlog/details/formatter/formatter.h"

namespace lwlog
{
	template<typename LogPolicy, template<typename...> typename StoragePolicy,
		typename ThreadingPolicy, template<typename> typename... Sinks>
	class logger : public interface::logger, private LogPolicy, public Sinks<ThreadingPolicy>...
	{
	private:
		using StoragePolicyT = typename StoragePolicy<Sinks<ThreadingPolicy>...>;
		using Storage = typename StoragePolicyT::storage;

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

#include "lwlog/logger_impl.h"
