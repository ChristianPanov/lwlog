#include "Benchmark.h"

#include "lwlog/logger.h"
#include "lwlog/lwlog.h"

#include <iostream>

int main()
{
	auto console = std::make_shared<lwlog::logger<lwlog::sinks::console_sink>>("CONSOLE");
	auto consoleFile = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("CONSOLE", "C:/Users/user/Desktop/TheLogs/LOGS.txt");

	console->add_pattern_attribute({ "{ATTR}", "%*", "NEW_ATTRIBUTE" });
<<<<<<< HEAD
	console->set_level_filter({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::critical });
=======
	console->set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::critical });
>>>>>>> d9d62518ee755773861ff331255bae3a7a32c1f7
	console->set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^ {ATTR}");

	{
		Timer timer("timer");
		console->critical("First critical message");
	}

	return 0;
}
