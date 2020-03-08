#include "lwlog/logger.h"
#include "lwlog/datetime.h"
#include "lwlog/formatter.h"

#include "lwlog/details/utilities.h"
#include "lwlog/details/duplex.h"

#include "lwlog/print.h"

#include "Benchmark.h"

#include "lwlog/details/file_helper.h"

#include "lwlog/sinks/sink.h"
#include "lwlog/sinks/sink_factory.h"
#include "lwlog/sinks/console_sink.h"
#include "lwlog/sinks/file_sink.h"
#include "lwlog/sinks/sink_level.h"

#include "lwlog/lwlog.h"
#include "lwlog/registry.h"

int main()
{
	auto console = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("LOGGER");
	auto console2 = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("LOGGER2");
	auto console3 = std::make_shared<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("LOGGER3");

	console->init_log_file("LOGS.txt","C:/Users/user/Desktop/TheLogs");

	lwlog::global_set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::warning });
	lwlog::global_set_pattern("^br_cyan^[%x] [%n]^reset^ ^br_magenta^[%l]^reset^: ^br_white^%v^reset^");
	console->set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::critical });
	console->set_pattern("^br_red^[%x] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	console->info("First info message");
	console3->warning("Warn!");

	lwlog::apply_to_all([](lwlog::logger_registry_interface* logger)
	{
		logger->info("That's a very important info message regarding engine architecture");
	});
	
	lwlog::global_set_pattern("^br_red^[%x] [%n]^reset^ ^br_magenta^[%l]^reset^: ^br_white^%v^reset^");
	lwlog::debug("IS THIS EVEN MORE GLOBAL AND GENERIC?");
	lwlog::get("LOGGER2")->warning("sad");
	return 0;
}
