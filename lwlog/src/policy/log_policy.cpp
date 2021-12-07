#include "log_policy.h"

namespace lwlog
{
	void forward_log_policy::log(sink_ptr sink, const details::log_message& log_msg)
	{
		sink->sink_it(log_msg);
	}

	void deferred_log_policy::log(sink_ptr sink, const details::log_message& log_msg)
	{
		m_storage.push_back({ sink, log_msg });
	}

	void deferred_log_policy::sink_logs()
	{
		for (const auto& [sink, log_msg] : m_storage)
		{
			sink->sink_it(log_msg);
		}
	}
}