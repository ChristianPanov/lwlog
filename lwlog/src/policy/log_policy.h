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

	template<
		std::size_t Capacity				= 1024,
		typename	OverflowPolicy			= block_overflow_policy,
		typename	ConcurrencyModelPolicy	= spsc_model_policy
	> struct asynchronous_policy
	{
		template<typename SinkStorage>
		struct backend
		{
			~backend();

			SinkStorage sink_storage;

			std::atomic<bool> shutdown;
			std::thread worker_thread;

			details::bounded_queue<
				Capacity, 
				details::record, 
				OverflowPolicy,
				ConcurrencyModelPolicy
			> queue;
		};

		template<typename SinkStorage>
		static void init(backend<SinkStorage>& backend);

		template<typename SinkStorage>
		static void log(backend<SinkStorage>& backend, const details::record& record);
	};
}

#include "log_policy_impl.h"