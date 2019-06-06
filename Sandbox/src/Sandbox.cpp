#include "lwlog/lwlog.h"

int main()
{
	std::string str1 = "test";
	std::string str2 = "for";

	lwlog::print("That's a {0} message {1} you. \n\n", str1, str2);

	std::shared_ptr<lwlog::logger> core_logger = std::make_shared<lwlog::logger>("LOGGER");
	std::shared_ptr<lwlog::logger> core_ldsdogger = std::make_shared<lwlog::logger>("LOGGER2");
	std::shared_ptr<lwlog::logger> core_logaager = std::make_shared<lwlog::logger>("LOGGER3");

	lwlog::registry::instance().display_all_loggers();

	lwlog::registry::instance().drop("LOGGER2");
	lwlog::print("\n");

	lwlog::registry::instance().display_all_loggers();

	core_logger->set_logLevel_visibility(lwlog::log_level::error | lwlog::log_level::critical);
	core_logger->set_pattern("[%x] [%n]: %v");
	core_logger->critical("A very critical message!");

	return 0;
}
