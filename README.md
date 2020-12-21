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

	lwlog::set_level_filter(lwlog::sink_level::debug | lwlog::sink_level::critical);
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
			lwlog::default_storage_policy,
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
	auto logger = std::make_shared<
		lwlog::logger<
			lwlog::default_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_color_sink, 
      lwlog::sinks::file_sink
		>
	>("LOGGER", "C:/Users/user/Desktop/LogFolder/LOGS.txt");

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
		lwlog::default_storage_policy,
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
## Logger configuration
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::default_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_color_sink
		>
	>("CONSOLE");
	
	return 0;
}
```
```default_storage_policy``` - convenienve alias for ```static_storage_policy```

```static_storage_policy``` - it configures the sink storage as an std::array - use it if you only set sinks in compile time and you know for sure you won't add sinks in at runtime, it is more lightweight than a dynamic sink storage.

```dynamic_storage_policy``` - it configures the sink storage as std::vector - use it if you may add sinks at runtime, or if you simply aren't sure if you are only going to use the compile-time set sinks.

```single_threaded_policy``` - configures the sinks with a placeholder mutex and locks - use it if you don't need thread-safety, it is more lightweight than thread-safe logger.

```multi_threaded_policy``` - configures the sinks with a mutex and locks for thread-safety.

## Usage TIPS
If you don't need to configure anything and if you want to have a simpler logger creation, you are always free to use the convenience aliases.
For example, you can create a logger simply by using one of these aliases:

```console_color_logger```- colored logger, sinks to stdout

```console_logger``` - non-colored logger, sinks to stdout

```file_logger``` - sinks to a file

Or if you want thread-safe loggers, just use:

```console_color_logger_mt``` - colored thread-safe logger, sinks to stdout

```console_logger_mt``` - non-colored thread-safe logger, sinks to stdout

```file_logger_mt``` - thread-safe logger, sinks to file

## Benchmarks
I haven't had the chance  to conduct proper benchmarks, but I have benchmarked against spdlog, as well as logging a single synchronous message
A single synchronous log call (single-threaded, formatted, and colored) takes ~8μs

#### lwlog (colored and formatted) vs spdlog (formatted) - Benchmarked with picobench(https://github.com/iboB/picobench)

```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.017 |    2125 |      - |   470588.2
             spdlog_bench |       8 |     0.487 |   60862 | 28.641 |    16430.5
            lwlog_bench * |      64 |     0.103 |    1603 |      - |   623781.7
             spdlog_bench |      64 |     3.171 |   49539 | 30.902 |    20186.1
            lwlog_bench * |     512 |     0.818 |    1597 |      - |   625916.9
             spdlog_bench |     512 |    38.332 |   74866 | 46.860 |    13357.1
            lwlog_bench * |    4096 |     7.457 |    1820 |      - |   549275.2
             spdlog_bench |    4096 |   278.632 |   68025 | 37.365 |    14700.4
            lwlog_bench * |    8192 |    23.543 |    2873 |      - |   347959.1
             spdlog_bench |    8192 |   642.031 |   78372 | 27.271 |    12759.5
===============================================================================
```
