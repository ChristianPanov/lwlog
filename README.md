# lwlog
Very fast C++17/C++20 logging library
# Install
```
git clone --recursive https://github.com/ChristianPanov/lwlog
```
# Features
- Written in modern C++17/20
- Very fast non-async logging (async logging is yet to be implemented)
- Verbosity levels
- Various log sinks
	- Console (stdout, stderr)
	- File
- Support for both compile-time and runtime sink configuration
- Custom sink configuration - each sink can have a unique log pattern and verbosity level
- Log formatting according to a custom user-defined pattern
- Custom pattern attributes
- Global logger registry
- High extensibility - very easy to add your own types of sinks and loggers
- Very configurable - it uses policy classes which you can just plug in based on your needs. At the same time, convenient easy-to-use predefined types are made for the
people who want simplicity without too much configuration. Most of the time you will be just fine with using the predefined types.
# Usage Examples
## Basic Usage
```cpp
#include "lwlog/lwlog.h"

int main()
{
	lwlog::info("Info message");
	lwlog::warning("Warning message");
	lwlog::error("Error message");
	lwlog::critical("Critical message");
	lwlog::debug("Debug message");

	lwlog::set_level_filter({ lwlog::sink_level::debug, lwlog::sink_level::critical });
	lwlog::info("Will not be displayed");

	lwlog::add_pattern_attribute({ "{foo}", "%f", "FOO" });
	lwlog::set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^ {foo}");
	lwlog::debug("Will be displayed according to the new pattern");

	return 0;
}
```
## Creating a logger
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::static_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_color_sink
		>
	>("CONSOLE");
	// or use the helper logger type aliases
	auto console2 = std::make_shared<lwlog::console_color_logger>("CONSOLE");
	
	console->set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	console->critical("First critical message");
	
	return 0;
}
```
## Multiple sinks (compile-time)
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::static_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_color_sink, 
      lwlog::sinks::file_sink
		>
	>("CONSOLE", "C:/Users/user/Desktop/LogFolder/LOGS.txt");

	logger->set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^"); // Color attributes will be ignored for the file sink
	logger->critical("First critical message"); // Log message will be distributed to both sinks
	
	return 0;
}
```
## Multiple sinks (runtime)
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console_sink = std::make_shared<lwlog::sinks::stdout_color_sink<lwlog::single_threaded_policy>>();
	auto file_sink = std::make_shared<lwlog::sinks::file_sink<lwlog::single_threaded_policy>>("C:/Users/user/Desktop/LogFolder/LOGS.txt");
	lwlog::primitives::sink_list sinks = { console_sink, file_sink };

	auto logger_iterator = std::make_shared<lwlog::null_logger>("ITERATOR", sinks.begin(), sinks.end());
	auto logger_sink_list = std::make_shared<lwlog::null_logger>("SINK_LIST", sinks);
	auto logger_single_sink = std::make_shared<lwlog::null_logger>("SINGLE_SINK", console_sink);
	auto logger_combined = std::make_shared<
		lwlog::logger<
			lwlog::static_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_color_sink
		>
	>("COMBINED", file_sink);

	return 0;
}
```
## Global operations
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
		lwlog::static_storage_policy,
		lwlog::single_threaded_policy,
		lwlog::sinks::stdout_color_sink
		>
	>("CONSOLE");
  
	auto file = std::make_shared<
		lwlog::logger<
		lwlog::static_storage_policy,
		lwlog::single_threaded_policy,
		lwlog::sinks::file_sink
		>
	>("FILE", "C:/Users/user/Desktop/LogFolder/LOGS.txt");
	
	//Pattern will be applied to all loggers present in the registry
	lwlog::global::set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	
	return 0;
}
```
