#pragma once

#include <string>
#include <vector>

#include "primitives.h"
#include "interface/logger_interface.h"
#include "details/log_message.h"
#include "sinks/sink.h"
#include "policy/sink_storage_policy.h"
#include "details/formatter/formatter.h"

namespace lwlog
{
	template<template<typename...> typename StoragePolicy, typename ThreadingPolicy, 
		template<typename> typename... Sinks>
	class logger : public interface::logger, public Sinks<ThreadingPolicy>...
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

		void set_pattern(std::string_view pattern) override;
		void add_pattern_attribute(primitives::attribute_t attribute) override;
		void set_level_filter(level_t level) override;

		void info(std::string_view message) override;
		void warning(std::string_view message) override;
		void error(std::string_view message) override;
		void critical(std::string_view message) override;
		void debug(std::string_view message) override;

		std::string name() const override;
		Storage& sinks();

	private:
		void log(std::string_view message, level_t level) override;

	private:
		details::log_message m_message;
		std::string m_name;
		Storage m_sink_buffer;
	};
}

#include "logger_impl.h"
