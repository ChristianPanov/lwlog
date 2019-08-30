#include "lwlog/lwlog.h"
#include "lwlog/registry.h"
#include "lwlog/utilities.h"
#include "lwlog/details.h"
#include "lwlog/datetime.h"

#include "Benchmark.h"

int main()
{
	std::string str1 = "test";
	std::string str2 = "for";

	lwlog::print("That's a {0} message {1} you. \n\n", str1, str2);

	auto console = std::make_unique<lwlog::logger>("CONSOLE");
	auto core_logger = std::make_unique<lwlog::logger>("LOGGER");
	auto core_logger2 = std::make_unique<lwlog::logger>("LOGGER2");
	auto core_logger3 = std::make_unique<lwlog::logger>("LOGGER3");

	lwlog::registry::display_all_loggers();

	lwlog::registry::drop("LOGGER2");
	lwlog::print("\n");

	lwlog::registry::display_all_loggers();

	console->set_logLevel_visibility(lwlog::log_level::info | lwlog::log_level::debug);
	console->set_pattern("^br_red^[%x] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	{
		Benchmark b;
		console->debug("A test debug message");
	}
	console->info("Some info log");

	core_logger->set_logLevel_visibility(lwlog::log_level::error | lwlog::log_level::critical);
	core_logger->set_pattern("[%x] [%n] [%l]: %v");
	core_logger->critical("A very critical message!");
	core_logger->error("Error!");

	core_logger3->set_pattern("[%weekday%] [%logger_name%] [%log_level%] [%log_level_abr%]: %message%");
	core_logger3->debug("Just debugging...");
	core_logger3->warning("A warning!!!");

	return 0;
}
