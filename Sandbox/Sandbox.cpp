#include "Benchmark.h"

#include "lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::default_log_policy,
			lwlog::default_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink
		>
	>("CONSOLE");

	console->set_level_filter(lwlog::level::info | lwlog::level::debug | lwlog::level::critical);
	console->set_pattern(".br_red([%T] [%n]) .green([%l]): .br_cyan(%v) TEXT.");

	{
		Timer timer("timer");
		console->critical("First critical message");
	}

	return 0;
}
