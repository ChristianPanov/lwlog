#pragma once

#include "sinks/sink.h"
#include "details/record.h"
#include "details/bounded_queue.h"

namespace lwlog
{
	constexpr std::size_t default_async_queue_size{ 1024 };

	struct synchronous_policy
	{
		template<typename ConcurrencyModelPolicy>
		struct backend
		{
			std::vector<sink_ptr> sink_storage;
		};

		template<typename ConcurrencyModelPolicy>
		static void init(backend<ConcurrencyModelPolicy>&) {};

		template<typename ConcurrencyModelPolicy>
		static void log(backend<ConcurrencyModelPolicy>& backend, const details::record& record);
	};

	template<
		std::size_t Capacity	= default_async_queue_size,
		typename OverflowPolicy = block_overflow_policy
	> 
	struct asynchronous_policy
	{
		template<typename ConcurrencyModelPolicy>
		struct backend
		{
			~backend();

			std::vector<sink_ptr> sink_storage;

			std::atomic<bool> shutdown;
			std::thread worker_thread;

			details::bounded_queue<
				Capacity, 
				details::record, 
				OverflowPolicy,
				ConcurrencyModelPolicy
			> queue;
		};

		template<typename ConcurrencyModelPolicy>
		static void init(backend<ConcurrencyModelPolicy>& backend);

		template<typename ConcurrencyModelPolicy>
		static void log(backend<ConcurrencyModelPolicy>& backend, const details::record& record);
	};
}

#include "log_policy_impl.h"