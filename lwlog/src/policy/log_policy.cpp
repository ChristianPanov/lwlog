#include "log_policy.h"

namespace lwlog
{
	struct deferred_log_policy::log_info
	{
		sink_ptr sink;
		details::record record;
	};

	std::vector<deferred_log_policy::log_info> deferred_log_policy::m_storage;

	void forward_log_policy::log(sink_ptr sink, const details::record& record)
	{
		sink->sink_it(record);
	}

	void deferred_log_policy::log(sink_ptr sink, const details::record& record)
	{
		m_storage.push_back({ sink, record });
	}

	void deferred_log_policy::sink_logs()
	{
		for (const auto& [sink, record] : m_storage)
		{
			sink->sink_it(record);
		}
	}
}