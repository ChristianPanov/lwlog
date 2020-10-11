#include "Benchmark.h"

#include "lwlog/lwlog.h"
#include "lwlog/logger.h"
#include "lwlog/sinks/stdout_color_sink.h"

#include <iostream>

int main()
{
	auto console = std::make_shared<lwlog::logger<lwlog::sinks::stdout_color_sink>>("CONSOLE");

	console->add_pattern_attribute({ "{ATTR}", "%*", "NEW_ATTRIBUTE" });
	console->set_level_filter({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::critical });
	console->set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^ {ATTR}");

	{
		Timer timer("timer");
		console->critical("First critical message");
	}

	return 0;
}
