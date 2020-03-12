#include "Benchmark.h"

#include "lwlog/logger.h"
#include "lwlog/lwlog.h"

#include <iostream>

int main()
{
	auto console = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("CONSOLE", "C:/Users/user/Desktop/TheLogs/LOGS.txt");
	//auto console2 = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("CONSOLE2");

	console->set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::critical });
	//console->set_pattern("^br_red^[%x] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	{
		Timer timer("Timer");
		console->critical("First critical message");
		//std::cout << "First critical message";
	}
	
	return 0;
}
