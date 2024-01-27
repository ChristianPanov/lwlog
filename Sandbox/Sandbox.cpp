#include "Benchmark.h"

#include "lwlog.h"

int main()
{
	using logger_config = lwlog::configuration<
		lwlog::enable_time,
		lwlog::enable_local_time,
		lwlog::disable_precise_units,
		lwlog::disable_thread_id, 
		lwlog::disable_process_id
	>;

	auto console = std::make_shared<
		lwlog::logger<
			logger_config,
			lwlog::asynchronous_policy<
				lwlog::default_async_queue_size,
				lwlog::default_overflow_policy
			>,
			lwlog::buffered_flush_policy<>,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink
		>
	>("CONSOLE");

	console->set_level_filter(lwlog::level::info | lwlog::level::debug | lwlog::level::critical);
	console->set_pattern("{nanosec}us - .br_red([%T] [%n]) .green([%l]): .br_cyan(%v) TEXT");

	{
		Timer timer("timer");
		console->critical("First critical message");
	}

	return 0;
}
