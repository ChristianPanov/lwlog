#pragma once

namespace lwlog::details
{
    inline record_base::record_base(std::string_view message, level log_level, const source_meta& meta)
		: log_level{ log_level }
		, meta{ meta }
	{
		message_buffer.append(message);
	}

	template<typename Config>
	record<Config>::record(std::string_view message, level log_level, const source_meta& meta, 
		const topic_registry<typename Config::topic_t>& topic_registry)
		: record_base{ message, log_level, meta }
		, m_topic_registry{ topic_registry }
	{}

	template<typename Config>
	const os::time_point_base& record<Config>::time_point() const
	{
		return dynamic_cast<const os::time_point_base&>(m_time_point);
	}

	template<typename Config>
	const os::execution_context_base& record<Config>::exec_context() const
	{
		return dynamic_cast<const os::execution_context_base&>(m_execution_context);
	}

	template<typename Config>
	const topic_registry_base& record<Config>::get_topic_registry() const
	{
		return dynamic_cast<const topic_registry_base&>(m_topic_registry);
	}
}