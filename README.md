[![Codacy Badge](https://api.codacy.com/project/badge/Grade/05f2384593ed49bbaa51fa2516793d99)](https://app.codacy.com/gh/ChristianPanov/lwlog?utm_source=github.com&utm_medium=referral&utm_content=ChristianPanov/lwlog&utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/christianpanov/lwlog/badge)](https://www.codefactor.io/repository/github/christianpanov/lwlog)\
Very fast C++17 logging library
# Install
```
git clone --recursive https://github.com/ChristianPanov/lwlog
```
# Design Highlights
- Extremely fast syncrhonous logging (other logging libraries promise you speed by being asycnrhonous, which is not always a good idea, because it's hard to identify at what point the program crashed, causes more overhead and you can easily lose important messages, lwlog promises you both speed, as fast as synchronous logging can get, and keeping all your messages)
- High extensibility - [very easy to add your own types of sinks and loggers](https://github.com/ChristianPanov/lwlog#creating-your-own-sink)
- Very configurable - lwlog uses policy classes which you can just plug in based on your needs. At the same time, convenient easy-to-use predefined types([convenience aliases](https://github.com/ChristianPanov/lwlog#convenience-logger-aliases)) are made for the
people who want simplicity without too much configuration. Most of the time you will be just fine with using the predefined types.
# Features
- Written in modern C++17
- Synchronous logging
- Forward(default, linear) and [deferred(non-linear)](https://github.com/ChristianPanov/lwlog#creating-your-own-sink) logging mechanisms
- Verbosity levels
- Various log sinks
	- Console (stdout, stderr)
	- File
	- Custom sinks (it's extremely easy to add your own custom sinks)
- Support for both compile-time and runtime sink configuration
- Custom sink configuration - each sink can have a unique log pattern and verbosity level
- Log formatting according to a custom user-defined pattern
- Global logger registry
# To be implemented
- Fmt-like formatting(As soon as std::format gets implemented in MSVC, fmt-like formatting will be implemented in lwlog)
- Meta-logging (also known as structured logging)
- Asyncrhonous logging
# Benchmarks
The benchmarks are still limited, since there still arent benchmarks for thread-safe logging, async logging, and loggers which sink to a file (they will be done)
#### lwlog (formatted, synchronous) vs spdlog (formatted, synchronous) - Benchmarked with picobench(https://github.com/iboB/picobench)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.015 |    1862 |      - |   536912.8
             spdlog_bench |       8 |     0.559 |   69900 | 37.530 |    14306.2
            lwlog_bench * |      64 |     0.096 |    1500 |      - |   666666.7
             spdlog_bench |      64 |     3.660 |   57181 | 38.121 |    17488.3
            lwlog_bench * |     512 |     0.764 |    1492 |      - |   669981.7
             spdlog_bench |     512 |   123.881 |  241955 |162.106 |     4133.0
            lwlog_bench * |    4096 |     6.319 |    1542 |      - |   648224.3
             spdlog_bench |    4096 |   331.658 |   80971 | 52.487 |    12350.1
            lwlog_bench * |    8192 |    14.872 |    1815 |      - |   550844.9
             spdlog_bench |    8192 |   846.085 |  103281 | 56.892 |     9682.2
===============================================================================
```
#### lwlog (colored and formatted, synchronous) vs spdlog (colored and formatted, synchronous) - Benchmarked with picobench(https://github.com/iboB/picobench)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.018 |    2312 |      - |   432432.4
             spdlog_bench |       8 |     1.292 |  161512 | 69.843 |     6191.5
            lwlog_bench * |      64 |     0.166 |    2590 |      - |   386007.2
             spdlog_bench |      64 |    14.400 |  225006 | 86.854 |     4444.3
            lwlog_bench * |     512 |     0.798 |    1559 |      - |   641362.9
             spdlog_bench |     512 |   122.694 |  239636 |153.694 |     4173.0
            lwlog_bench * |    4096 |     6.724 |    1641 |      - |   609134.0
             spdlog_bench |    4096 |   906.999 |  221435 |134.884 |     4516.0
            lwlog_bench * |    8192 |    14.081 |    1718 |      - |   581781.0
             spdlog_bench |    8192 |  1845.808 |  225318 |131.086 |     4438.2
===============================================================================
```
#### lwlog (colored and formatted, synchronous) vs spdlog (formatted, synchronous) - Benchmarked with picobench(https://github.com/iboB/picobench)
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
#### lwlog (forward(default) logging) vs lwlog (deferred logging) - Benchmarked with picobench(https://github.com/iboB/picobench)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
   lwlog_deferred_bench * |       8 |     0.003 |     387 |      - |  2580645.2
      lwlog_forward_bench |       8 |     0.015 |    1912 |  4.935 |   522875.8
   lwlog_deferred_bench * |      64 |     0.021 |     329 |      - |  3033175.4
      lwlog_forward_bench |      64 |     0.086 |    1351 |  4.100 |   739884.4
   lwlog_deferred_bench * |     512 |     0.232 |     453 |      - |  2204046.5
      lwlog_forward_bench |     512 |     0.634 |    1237 |  2.728 |   808080.8
   lwlog_deferred_bench * |    4096 |     1.518 |     370 |      - |  2698109.5
      lwlog_forward_bench |    4096 |     6.875 |    1678 |  4.529 |   595747.2
   lwlog_deferred_bench * |    8192 |     3.074 |     375 |      - |  2664671.6
      lwlog_forward_bench |    8192 |    10.454 |    1276 |  3.401 |   783593.5
===============================================================================
```
# Usage
## Basic Usage
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::default_log_policy,
			lwlog::default_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink>
			>("CONSOLE");
	// or use the convenience logger aliases
	auto console2 = std::make_shared<lwlog::console_logger>("CONSOLE");
	
	console->set_level_filter(lwlog::level::info | lwlog::level::debug | lwlog::level::critical);
	console->set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	console->critical("First critical message");
	
	return 0;
}
```
## Convenience logger aliases
In the file lwlog.h you can see several convenience aliases at your disposal.\
They are intended for ease of use, so I encourage you to use them instead of the more complex way of creating loggers directly through the logger class.\
They are predefined with default configurations, so unless you need more special functionality, stick to using them.\
```lwlog::basic_logger``` - configured with a standard log mechanism(forward logging) and a standard sink storage(dynamic storage), not thread-safe
```cpp
#include "lwlog/lwlog.h"

int main()
{
 	// logger to stdout with default configuration
	auto console = std::make_shared<lwlog::basic_logger<sinks::stdout_sink>>("CONSOLE");
	
	return 0;
}
```
```lwlog::console_logger``` - basic_logger which sinks to stdout\
```lwlog::file_logger``` - basic_logger which sinks to a file
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<console_logger>("CONSOLE")
	auto file = std::make_shared<file_logger>("FILE", "C:/Users/user/Desktop/LogFolder/LOGS.txt");
	return 0;
}
```
```lwlog::null_logger``` - A null logger is simply a logger with default configuration but without any sinks. Use it if you don't want compile time sinks and you are only interested in adding sinks later at runtime
```cpp
auto logger = std::make_shared<lwlog::null_logger>("LOGGER");
```
## Switching off logging
If you want to be able to turn off logging completely, you can use the preprocessor directives.
```cpp
#LWLOG_DISABLE
#LWLOG_ERROR_OFF
#include "lwlog/lwlog.h"

int main()
{
	LWLOG_SET_PATTERN("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	LWLOG_SET_LEVEL_FILTER(lwlog::sink_level::error | lwlog::sink_level::critical);
	LWLOG_ERROR("Error message");
	return 0;
}
```
These directives use the default loggger and are present in the lwlog.h file.\
They will log unless you disable logging with LWLOG_DISABLE(should always be at the very top of the file), or you switch off a specific logging level.\
Levels can be switched off at runtime as well, just by using the LWLOG_SET_LEVEL_FILTER directive.\
You can also set a pattern and set a filter for log levels.\
If logging is disabled, the directives expand to nothing.
## Formatting
Formatting is handled with a pay for what you need approach. Currently, there are still aspects which could be optimized further, which will result in even more literal meaning of paying for what you need.\
The user is able to set a pattern, by which the log messages will be formatted. This pattern is an internal to the library language, which is a sequence of formatting flags, characters and color codes(which are optional). It allows flexibility in terms of configuring the output information in the most appropriate for the situation way, allowing as meaningful log output as possible.\
How is formatting done? - A pattern is set, and then it gets compiled by the library. Compilation is done in the ```lwlog::details::pattern``` class. It firts parses the pattern, and extracts the formatting flags, which are then used to retrieve only the formatters the pattern will need. In the end, all the retrieved formatters are called on the pattern, and all formatting flags are replaced with their corresponding values.
## Multiple sinks (compile-time)
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto logger = std::make_shared<
		lwlog::logger<
			lwlog::default_log_policy,
			lwlog::default_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink, 
      			lwlog::sinks::file_sink>
			>("LOGGER", "C:/Users/user/Desktop/LogFolder/LOGS.txt");

	// Color attributes will be ignored for the file sink
	logger->set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	logger->critical("First critical message"); // Log message will be distributed to both sinks
	
	return 0;
}
```
## Multiple sinks (runtime)
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console_sink = std::make_shared<lwlog::sinks::stdout_sink<lwlog::single_threaded_policy>>();
	auto file_sink = std::make_shared<lwlog::sinks::file_sink<lwlog::single_threaded_policy>>("C:/Users/user/Desktop/LogFolder/LOGS.txt");
	lwlog::primitives::sink_list sinks = { console_sink, file_sink };

	auto logger_iterator = std::make_shared<lwlog::null_logger>("ITERATOR", sinks.begin(), sinks.end());
	auto logger_sink_list = std::make_shared<lwlog::null_logger>("SINK_LIST", sinks);
	auto logger_single_sink = std::make_shared<lwlog::null_logger>("SINGLE_SINK", console_sink);
	auto logger_combined = std::make_shared<
		lwlog::logger<
			lwlog::default_log_policy,
			lwlog::static_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink>
			>("COMBINED", file_sink);

	return 0;
}
```
## Default logger
The default logger is a logger object delievered to you by the library itself.\
It's registered in the logger registry, it's global, it has default configuration and is NOT thread-safe, sinks to stdout.\
It's convenient if you just need the logging functionality, but don't want to create loggers by yourself. You can access it from everywhere in your application.
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

	lwlog::set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	lwlog::debug("Will be displayed according to the new pattern");

	return 0;
}
```
## Global operations
In order to apply a logger function to all loggers present in the registry, you can use the function ```apply_to_all()``` in such manner
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<lwlog::console_logger>("CONSOLE");
	auto file = std::make_shared<lwlog::file_logger>("FILE", "C:/Users/user/Desktop/LogFolder/LOGS.txt");
	
	//Pattern will be applied to all loggers present in the registry
	lwlog::apply_to_all([](lwlog::primitives::logger_ptr logger)
		{
			logger->set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^ TEXT");
		});
	
	return 0;
}
```
## Accessing a logger from the global registry by name
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<lwlog::console_logger>("CONSOLE");
	
	lwlog::get("CONSOLE")->critical("First critical message");
	
	return 0;
}
```
## Creating your own sink
As I said and promissed, lwlog is extremely easy to extend. Let's give an example with sinks.\
To create your own sink, all you have to do is to inherit from ```lwlog::interface::sink``` and implement a ```sink_it()``` function. That's it.
#### Example with an existing sink implementation
```cpp
#include "policy/sink_color_policy.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stdout_sink
		: public sink<colored_policy, ThreadingPolicy>
		, public details::stream
	{
	public:
		stdout_color_sink() : details::stream(stdout) {}
		void sink_it(std::string_view message) override
		{
			details::stream::write(message);
		}
	};
}
```
Here we inherit from the sink base class, and configure it to be colored. Whether it's thread-safe or not is left up to the one using the sink.\
The color policy could be either colored(```lwlog::colored_policy```) or non-colored (```lwlog::uncolored_policy```).\
The non-colored policy will drop the color flags in the pattern instead of processing them, but will not ignore them. Using ```lwlog::colored_policy``` is most suitable for console sinks, since it relies on console specific color codes.\
We only need the ```sink_it()``` function, which is called as the actual log call. It can do whatever you want it to do - write to console, write to file, write to file in some fancy way, write to another application, etc.
```cpp
#include "policy/sink_color_policy.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class new_custom_sink
		: public sink<colored_policy, ThreadingPolicy>
	{
	public:
		void sink_it(std::string_view message) override
		{
			// sink message to somewhere
		}
	};
}
```
## Logger configuration
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::default_log_policy,
			lwlog::default_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink>
			>("CONSOLE");
	
	return 0;
}
```
```lwlog::default_log_policy``` - convenience alias for ```forward_log_policy```\
```lwlog::forward_log_policy``` - your standard linear logging mechanism. You call a log function, and it's outputted to the specified sink\
```lwlog::deferred_log_policy``` - as the name suggests, log calls are deffered for later use. When a log function is called, instead of directly sinking the data, it's stored in a storage for later use. This method provides very low latency, but use it only if you are sure you don't need your logs immediately\
```lwlog::default_storage_policy``` - convenienve alias for ```static_storage_policy```\
```lwlog::static_storage_policy``` - it configures the sink storage as an std::array - use it if you only set sinks in compile time and you know for sure you won't add sinks in at runtime, it is more lightweight than a dynamic sink storage\
```lwlog::dynamic_storage_policy``` - it configures the sink storage as std::vector - use it if you may add sinks at runtime, or if you simply aren't sure if you are only going to use the compile-time set sinks\
```lwlog::single_threaded_policy``` - configures the sinks with a placeholder mutex and locks - use it if you don't need thread-safety, it is more lightweight than thread-safe logger\
```lwlog::multi_threaded_policy``` - configures the sinks with a mutex and locks for thread-safety
## Deferred logging
Deferred logging provides extremely low latency, however it's only applicable when you don't need the logs to be outputted immediately.\
The low latency comes from the fact that with deferred logging a log call doesn't sink and doesn't format anything, it only stores data.\
This data is sinked and formatted at a later stage, only when needed.
There is one problem with it - all log information will be lost if there is an application crash and you haven't sinked the deferred logs. On crash, all deferred logs should be automatically sinked, that's the solution that I will be working on.
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::deferred_log_policy,
			lwlog::default_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink>
			>("CONSOLE");
	
	console->critical("First critical message");
	console->info("First info message");
	console->debug("First debug message");
	
	console->sink_logs();
	
	return 0;
}
```
By calling ```sink_logs()``` you sink all the logs that are deferred for later use to their respective sinks with their respective patterns.\
If ```sink_logs()``` is called by a forward logging logger it will emit a warning.
## Thread-safety
Both the sinks and the logger classes expect a threading policy as a template parameter, which will determine whether they will be thread-safe or not.
However, if you want to use the convenienve aliases I meantioned above, you need to keep in mind they are not thread-safe.\
And for that reason all of them have a thread-safe analog whith the same name and an _mt suffix.\
```lwlog::basic_logger_mt```, ```lwlog::console_logger_mt```, ```lwlog::file_logger_mt```, ```lwlog::null_logger_mt```
