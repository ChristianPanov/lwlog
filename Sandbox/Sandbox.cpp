#include "Benchmark.h"

#include "lwlog.h"

static size_t allocation_count = 0;

// Override global new operator
void* operator new(size_t size) 
{
	++allocation_count;
	return std::malloc(size); // Use malloc for allocation
}

int main()
{
	using logger_config = lwlog::configuration<
		lwlog::disable_local_time,
		lwlog::disable_thread_id, 
		lwlog::disable_process_id,
		lwlog::disable_topics
	>;

	auto console = std::make_shared<
		lwlog::logger<
			lwlog::default_config,
			lwlog::default_memory_buffer_limits,
			lwlog::asynchronous_policy<
				lwlog::default_overflow_policy,
				lwlog::default_async_queue_size,
				lwlog::default_thread_affinity
			>,
			lwlog::immediate_flush_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink
		>
	>("CONSOLE");

	console->set_level_filter(lwlog::level::info | lwlog::level::debug | lwlog::level::critical);
	console->set_pattern(".red([%T] [%n]) .dark_green([:^12{level}]): .cyan(%v) TEXT");

	{
		Timer timer("timer");
		//lwlog::details::alignment_formatter::format(buffer, info);
		console->critical("First {} critical message {}");
	}

	std::cout << "Total allocations: " << allocation_count << "\n";

	return 0;
}

// Total Allocations - 190