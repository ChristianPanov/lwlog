#include "Benchmark.h"

#include "lwlog/logger.h"
#include "lwlog/lwlog.h"

#include <iostream>

int main()
{
	auto console = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("CONSOLE", "C:/Users/user/Desktop/TheLogs/LOGS.txt");
	auto console2 = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("CONSOLE2");

	console->add_pattern_attribute({ "[ATTR]", "%*", "NEW_ATTRIBUTE" });
	console->set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::critical });
	console->set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^ [ATTR]");
	console->critical("First critical message");

	lwlog::global::set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::warning });
	lwlog::global::set_pattern("^br_cyan^[%T] [%n]^reset^ ^br_magenta^[%l]^reset^: ^br_white^%v^reset^");

	console2->info("Info message");

	lwlog::apply_to_all([](lwlog::interface::logger_ptr logger)
		{
			logger->info("Dispatched to all loggers in registry");
		});

	lwlog::debug("IS THIS EVEN MORE GLOBAL AND GENERIC?");

	lwlog::get("CONSOLE")->warning("Global");
	return 0;
}