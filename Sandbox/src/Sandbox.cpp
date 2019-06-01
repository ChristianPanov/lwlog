#include "lwlog/lwlog.h"

int main()
{
	std::shared_ptr<lwlog::logger> core_logger = std::make_shared<lwlog::logger>("LOGGER");
	std::shared_ptr<lwlog::logger> core_ldsdogger = std::make_shared<lwlog::logger>("ELEMENT");
	std::shared_ptr<lwlog::logger> core_logaager = std::make_shared<lwlog::logger>("QUASAR");

	lwlog::registry::instance().display_all_loggers();

	lwlog::registry::instance().drop("ELEMENT");
	lwlog::print("\n");

	lwlog::registry::instance().display_all_loggers();

	core_logger->set_logLevel_visibility(lwlog::log_level::all);
	core_logger->set_pattern("[%x] [%n]: %v");
	core_logger->critical("A very critical message!");

	return 0;
}