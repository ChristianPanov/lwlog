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
	auto console = std::make_unique<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("LOGGER");
	auto console2 = std::make_unique<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("LOGGER2");
	auto console3 = std::make_unique<lwlog::logger<lwlog::sinks::console_sink, lwlog::sinks::file_sink>>("LOGGER3");

	console->set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::critical });
	console->set_pattern("^br_red^[%x] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	console->info("First info message");

	lwlog::set_pattern("^br_cyan^[%x] [%n]^reset^ ^br_magenta^[%l]^reset^: ^br_white^%v^reset^");
	lwlog::set_level_visibility({ lwlog::sink_level::debug});
	lwlog::debug("IS THIS EVEN MORE GLOBAL AND GENERIC?");

	// TO FIX: Doesn't output anything. There is something wrong with the get method from the registry class.
	// If I turn every std::shared_ptr to just raw pointer in the registry class it works fine and outputs the log,
	// but with an std::shared_ptr it does not output
	lwlog::registry::instance().get("LOGGER")->critical("CRITICAL MESSAGE");

	return 0;
}
