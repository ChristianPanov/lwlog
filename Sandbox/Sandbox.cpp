#include "Benchmark.h"

#include "lwlog.h"

int main()
{
	using logger_config = lwlog::configuration<
		lwlog::enable_time,
		lwlog::disable_local_time,
		lwlog::disable_precise_units,
		lwlog::disable_thread_id, 
		lwlog::disable_process_id,
		lwlog::enable_topics
	>;

	auto console = std::make_shared<
		lwlog::logger<
			logger_config,
			lwlog::asynchronous_policy<
				lwlog::default_async_queue_size,
				lwlog::overwrite_last_overflow_policy
			>,
			lwlog::buffered_flush_policy<>,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink
		>
	>("CONSOLE");

	console->set_level_filter(lwlog::level::info | lwlog::level::debug | lwlog::level::critical);
	console->set_pattern("{full_topic} .red([%T] [%n]) .dark_green([%l]): .cyan(%v) TEXT");

	console->set_topic_separator("|");

	console->start_topic("Topic 1");
	console->start_topic("Topic 2");
	console->start_topic("Topic 3");
	console->start_topic("Topic 4");

	{
		Timer timer("timer");
		console->critical("First critical message");
	}

	return 0;
}
