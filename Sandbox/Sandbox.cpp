#include "Benchmark.h"

#include "lwlog/logger.h"
#include "lwlog/lwlog.h"

#include <iostream>
#include <list>

int main()
{
	auto logger1 = std::make_shared<lwlog::logger<lwlog::sinks::console_sink>>("logger1");

	auto consoleSink = std::make_shared<lwlog::sinks::console_sink>();
	auto fileSink = std::make_shared<lwlog::sinks::file_sink>();

	std::initializer_list<lwlog::sinks::sink_ptr> listt = { consoleSink, fileSink };
	std::vector<lwlog::sinks::sink_ptr> vecc = { consoleSink, fileSink };

	auto logger2 = std::make_shared<lwlog::logger<>>("logger2", vecc.begin(), vecc.end());

	/*
	auto console = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("CONSOLE");
	auto console2 = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("CONSOLE2");

	console->init_log_file("LOGS.txt","C:/Users/user/Desktop/TheLogs");

	console->set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::critical });
	console->set_pattern("^br_red^[%x] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	console->critical("First critical message");

	lwlog::global_set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::warning });
	lwlog::global_set_pattern("^br_cyan^[%x] [%n]^reset^ ^br_magenta^[%l]^reset^: ^br_white^%v^reset^");

	console2->info("Info message");

	lwlog::apply_to_all([](lwlog::logger_interface* logger)
	{
		logger->info("Dispatched to all loggers in registry");
	});

	lwlog::debug("IS THIS EVEN MORE GLOBAL AND GENERIC?");

	lwlog::get("CONSOLE2")->warning("Global");
	*/
	return 0;
}
