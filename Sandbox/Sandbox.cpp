#include "lwlog/lwlog.h"

int main()
{
	std::string str1 = "test";
	std::string str2 = "for";

	lwlog::print("That's a {0} message {1} you. \n\n", str1, str2);

	auto core_logger = std::make_unique<lwlog::logger>("LOGGER");
	auto core_logger2 = std::make_unique<lwlog::logger>("LOGGER2");
	auto core_logger3 = std::make_unique<lwlog::logger>("LOGGER3");

	lwlog::registry::display_all_loggers();

	lwlog::registry::drop("LOGGER2");
	lwlog::print("\n");

	lwlog::registry::display_all_loggers();

	core_logger->set_logLevel_visibility(lwlog::log_level::error | lwlog::log_level::critical);
	core_logger->set_pattern("[%x] [%n] [%l]: %v");
	core_logger->critical("A very critical message!");

	return 0;
}