#pragma once

#include "level.h"
#include "sinks/sink.h"
#include "details/bounded_queue.h"
#include "details/argument_format.h"
#include "details/source_meta.h"

namespace lwlog
{
	inline constexpr std::size_t default_async_queue_size{ 1024 };

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
		static void log(backend<ConcurrencyModelPolicy>& backend, std::string_view message, 
			level t_level, const details::source_meta& meta, details::format_args_list args);
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

			std::atomic_bool shutdown;
			std::thread worker_thread;

			struct queue_item;
			details::bounded_queue<
				Capacity, 
				queue_item,
				OverflowPolicy,
				ConcurrencyModelPolicy
			> queue;
		};

		template<typename ConcurrencyModelPolicy>
		static void init(backend<ConcurrencyModelPolicy>& backend);

		template<typename ConcurrencyModelPolicy>
		static void log(backend<ConcurrencyModelPolicy>& backend, std::string_view message,
			level t_level, const details::source_meta& meta, details::format_args_list args);
	};
}

#include "log_policy_impl.h"