#include "lwlog/lwlog.h"
#include "lwlog/registry.h"
#include "lwlog/utilities.h"
#include <chrono>
#include <tuple>
#include <map>
#include <string>

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

	console->set_logLevel_visibility(lwlog::log_level::all);
	console->set_pattern("[%x] [%n] [%l]: %v");
	console->debug("A test debug message");

	core_logger->set_logLevel_visibility(lwlog::log_level::error | lwlog::log_level::critical);
	core_logger->set_pattern("[%x] [%n] [%l]: %v");
	core_logger->critical("A very critical message!");
	core_logger->error("Error!");

	core_logger3->set_pattern("[%a] [%n] [%l] [%L]: %v");
	core_logger3->debug("Just debugging...");
	core_logger3->warning("A warning!!!");

	return 0;
}