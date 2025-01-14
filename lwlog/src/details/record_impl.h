#pragma once

namespace lwlog::details
{
	template<typename Config, typename BufferLimits>
	record<Config, BufferLimits>::record(std::string_view message, level log_level, const source_meta& meta,
		const topic_registry<typename Config::topic_t>& topic_registry)
		: log_level{ log_level }
		, meta{ meta }
		, m_topic_registry{ topic_registry }
	{
		message_buffer.append(message);
	}

	template<typename Config, typename BufferLimits>
	const os::time_point_base& record<Config, BufferLimits>::time_point() const
	{
		return dynamic_cast<const os::time_point_base&>(m_time_point);
	}

	template<typename Config, typename BufferLimits>
	const os::execution_context_base& record<Config, BufferLimits>::exec_context() const
	{
		return dynamic_cast<const os::execution_context_base&>(m_execution_context);
	}

	template<typename Config, typename BufferLimits>
	const topic_registry_base& record<Config, BufferLimits>::get_topic_registry() const
	{
		return dynamic_cast<const topic_registry_base&>(m_topic_registry);
	}
}