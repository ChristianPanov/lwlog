#pragma once

#include "level.h"
#include "sinks/sink.h"
#include "details/bounded_queue.h"
#include "details/source_meta.h"
#include "details/topic_registry.h"
#include "details/adaptive_waiter.h"

#include "details/argument_formatter/argument_format.h"
#include "details/argument_formatter/argument_buffers_pool.h"

namespace lwlog
{
	inline constexpr std::uint64_t default_thread_affinity{ 0xFFFFFFFFFFFFFFFF };
	inline constexpr std::size_t default_async_queue_size{ 1024 };

	struct synchronous_policy
	{
		template<typename BufferLimits, typename ConcurrencyModelPolicy>
		struct backend
		{
			details::memory_buffer<BufferLimits::message> message_buffer;
			char args_buffers[BufferLimits::arg_count][BufferLimits::argument];

			std::vector<sink_ptr<BufferLimits>> sink_storage;
			details::topic_registry topics;
		};

		template<typename BufferLimits, typename ConcurrencyModelPolicy>
		static void init(backend<BufferLimits, ConcurrencyModelPolicy>&) {}

		template<typename BufferLimits, typename ConcurrencyModelPolicy, typename... Args>
		static void log(backend<BufferLimits, ConcurrencyModelPolicy>& backend, const char* const message,
			level log_level, const details::source_meta& meta, Args&&... args);
	};

	template<
		typename OverflowPolicy	= block_overflow_policy,
		std::size_t Capacity = default_async_queue_size,
		std::uint64_t ThreadAffinity = default_thread_affinity
	> 
	struct asynchronous_policy
	{
		template<typename BufferLimits, typename ConcurrencyModelPolicy>
		struct backend
		{
			~backend();

			details::memory_buffer<BufferLimits::message> message_buffer;
			details::argument_buffers_pool<BufferLimits> arg_buffers_pool;

			std::vector<sink_ptr<BufferLimits>> sink_storage;
			details::topic_registry topics;

			std::atomic_flag has_work;
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

		template<typename BufferLimits, typename ConcurrencyModelPolicy>
		static void init(backend<BufferLimits, ConcurrencyModelPolicy>& backend);

		template<typename BufferLimits, typename ConcurrencyModelPolicy, typename... Args>
		static void log(backend<BufferLimits, ConcurrencyModelPolicy>& backend, const char* const message, 
			level log_level, const details::source_meta& meta, Args&&... args);

	private:
		template<typename BufferLimits, typename ConcurrencyModelPolicy>
		static void process_item(backend<BufferLimits, ConcurrencyModelPolicy>& backend);
	};
}

#include "log_policy_impl.h"