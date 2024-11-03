#pragma once

#include "configuration.h"
#include "source_meta.h"
#include "topic_registry.h"
#include "os/time_point.h"
#include "os/os.h"

namespace lwlog::details
{
	struct record_base
	{
		record_base() = default;
		record_base(std::string_view message, level log_level, const source_meta& meta);
		virtual ~record_base() = default;

		virtual const os::time_point_base& time_point() const = 0;
		virtual const os::execution_context_base& exec_context() const = 0;
		virtual const topic_registry_base& get_topic_registry() const = 0;

		std::string_view message;
		level log_level;
		source_meta meta;
	};

	template<typename Config>
	struct record : public record_base
	{
		record() = default;
		record(std::string_view message, level log_level, const source_meta& meta, 
			const topic_registry<typename Config::topic_t>& topic_registry);

		const os::time_point_base& time_point() const override;
		const os::execution_context_base& exec_context() const override;
		const topic_registry_base& get_topic_registry() const override;

	private:
		const os::time_point<
			typename Config::local_time_t
		> m_time_point{};

		const os::execution_context<
			typename Config::thread_id_t,
			typename Config::process_id_t
		> m_execution_context{};

		const topic_registry<
			typename Config::topic_t
		>& m_topic_registry;
	};
}

#include "record_impl.h"