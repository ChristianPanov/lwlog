#pragma once

#include "sinks/sink.h"
#include "details/record.h"
#include "details/bounded_queue.h"

namespace lwlog
{
	struct synchronous_policy
	{
		template<typename SinkStorage>
		struct backend
		{
			SinkStorage sink_storage;
		};

		template<typename SinkStorage>
		static void init(backend<SinkStorage>&) {};

		template<typename SinkStorage>
		static void log(backend<SinkStorage>& backend, const details::record& record);
	};

	template<std::size_t Capacity, typename OverflowPolicy>
	struct asynchronous_policy
	{
		template<typename SinkStorage>
		struct backend
		{
			~backend();

			std::atomic<bool> shutdown;
			std::thread worker_thread;
			SinkStorage sink_storage;

			details::bounded_queue<
				Capacity, 
				details::record, 
				OverflowPolicy
			> queue;
		};

		template<typename SinkStorage>
		static void init(backend<SinkStorage>& backend);

		template<typename SinkStorage>
		static void log(backend<SinkStorage>& backend, const details::record& record);
	};
}

#include "log_policy_impl.h"