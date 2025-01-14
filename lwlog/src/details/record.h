#pragma once

#include "configuration.h"
#include "source_meta.h"
#include "topic_registry.h"
#include "os/time_point.h"
#include "os/os.h"
#include "details/memory_buffer.h"

namespace lwlog::details
{
	template<typename Config, typename BufferLimits>
	struct record
	{
		record() = default;
		record(std::string_view message, level log_level, const source_meta& meta, 
			const topic_registry<typename Config::topic_t>& topic_registry);

		const os::time_point_base& time_point() const override;
		const os::execution_context_base& exec_context() const override;
		const topic_registry_base& get_topic_registry() const override;

	public:
		memory_buffer<BufferLimits::message> message_buffer;
		level log_level;
		source_meta meta;

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