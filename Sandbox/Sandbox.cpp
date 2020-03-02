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

	//console->init_log_file("LOGS.TXT", "C:/Users/user/Desktop/MyBitch");

	//lwlog::level_init_list levels{ lwlog::sink_level::info, lwlog::sink_level::debug };
	console->set_level_visibility({ lwlog::sink_level::info, lwlog::sink_level::debug, lwlog::sink_level::critical });
	console->set_pattern("^br_red^[%x] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	console->info("First info message");

	lwlog::registry::instance().get("LOGGER")->critical("CRITICAL MESSAGE");
	lwlog::get("LOGGER")->info("OKAY THATS PRETTY GLOBAL");
	//console->debug("First debug message");
	//console->critical("First critical message");

	lwlog::set_pattern("^br_cyan^[%x] [%n]^reset^ ^br_magenta^[%l]^reset^: ^br_white^%v^reset^");
	lwlog::set_level_visibility({ lwlog::sink_level::debug});
	lwlog::debug("IS THIS EVEN MORE GLOBAL AND GENERIC?");

	return 0;
}

/*
	auto mySink = std::make_unique<lwlog::sinks::file_sink>();
	mySink->init_log_file("LOGS.TXT", "C:/Users/user/Desktop/MyBitch");
	mySink->set_level_visibility(lwlog::level::info | lwlog::level::debug);
	mySink->set_pattern("[%x] [%n] [%l]: %v");
	mySink->log("Some info message", lwlog::level::info);
	mySink->log("Some debug message", lwlog::level::debug);
*/

/*
	auto console = std::make_unique<lwlog::logger>("CONSOLE");
	console->set_level_visibility(lwlog::level::info | lwlog::level::debug);
	console->set_pattern("^br_red^[%x] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");

	console->backtrace(32);
	console->set_backtrace_stamp("[BACKTRACE]");

	console->info("First info message");

	console->debug("First debug message");
	console->info("Second info message");
	console->debug("Second info message");

	lwlog::print("\n\n\n\n");

	console->display_backtrace();
*/

/*
	details::file_helper file;

	file.open("logs.txt", "C:/Users/user/Desktop/MyBitch", details::file_helper::append::on);
	file.write("Hey bro \n Some logs for you ;) \n");
	lwlog::print("Filename: {0}\n", file.get_filename());
	file.close();
*/

/*
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

	console->set_level_visibility(lwlog::level::info | lwlog::level::debug);
	console->set_pattern("^br_red^[%x] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	{
		Benchmark b;
		console->info("Some info log");
	}

	core_logger->set_level_visibility(lwlog::level::error | lwlog::level::critical);
	core_logger->set_pattern("[%x] [%n] [%l]: %v");
	core_logger->critical("A very critical message!");
	core_logger->error("Error!");

	core_logger3->set_pattern("[%weekday%] [%logger_name%] [%log_level%] [%log_level_abr%]: %message%");
	core_logger3->debug("Just debugging...");
	core_logger3->warning("A warning!!!");
*/
