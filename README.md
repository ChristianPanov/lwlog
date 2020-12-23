[![Codacy Badge](https://api.codacy.com/project/badge/Grade/05f2384593ed49bbaa51fa2516793d99)](https://app.codacy.com/gh/ChristianPanov/lwlog?utm_source=github.com&utm_medium=referral&utm_content=ChristianPanov/lwlog&utm_campaign=Badge_Grade)

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
# Benchmarks
I haven't had the chance  to conduct proper benchmarks, but I have benchmarked against spdlog, as well as logging a single synchronous message.\
A single synchronous log call (single-threaded, formatted, and colored) takes ~8μs\
(That is NOT proper benchmarking, it is ego boost in terms of performance. A proper benchmark would be to benchmark a lots of logs and get the average of it, although lwlog is surprisingly very consistent with it's latency, so these ~8μs are actually an accurate measurment).
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
			lwlog::sinks::stdout_color_sink>
			>("CONSOLE");
	// or use the convenience logger aliases
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
			lwlog::default_log_policy,
			lwlog::default_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_color_sink, 
      			lwlog::sinks::file_sink>
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
## Global logger
The global logger is a logger object delievered to you by the library itself. It's registered in the logger registry, it has default configuration and is NOT thread-safe, sinks to stdout. It's convenient if you just need the logging functionality, but don't want to create loggers by yourself. You can access it from everywhere in your application.
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
## Global operations
There are two convenient global operations. set_pattern() and set_level_filter(). Make no mistake from the name, they are not global because they process the global logger, they are global because they are processed for each logger that's present in the registry.
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<lwlog::console_color_logger>("CONSOLE");
	auto file = std::make_shared<lwlog::file_logger>("FILE", "C:/Users/user/Desktop/LogFolder/LOGS.txt");
	
	//Pattern will be applied to all loggers present in the registry
	lwlog::global::set_pattern("^br_red^[%T] [%n]^reset^ ^green^[%l]^reset^: ^br_cyan^%v^reset^");
	
	return 0;
}
```
## Accessing a logger from the global registry by name
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<lwlog::console_color_logger>("CONSOLE");
	
	lwlog::get("CONSOLE")->critical("First critical message");
	
	return 0;
}
```
## Creating your own sink
As I said and promissed, lwlog is extremely easy to extend. Let's give an example with sinks.\
To create your own sink, all you have to do is to inherit from lwlog::interface::sink and implement a sink_it() function. That's it.\
#### Example with an existing sink implementation
```cpp
#include "policy/sink_color_policy.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stdout_color_sink
		: public sink<colored_policy, ThreadingPolicy>
		, public details::stream
	{
	public:
		stdout_color_sink() : details::stream(stdout) {};
		void sink_it(std::string_view message) override
		{
			details::stream::write(message);
		}
	};
}
```
Here we inherit from the sink base class, and configure it to be colored. Whether it's thread-safe or not is left up to the one using the sink.\
The color policy could be either colored(```colored_policy```) or non-colored (```uncolored_policy```).\
The non-colored policy will drop the color flags in the pattern instead of processing them, but will not ignore them.\
We only need the sink_it() function, which is called as the actual log call. It can do whatever you want it to do - write to console, write to file, write to file in some fancy way, write to another application, etc.
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
## Convenience logger aliases
In the file lwlog.h you can see several convenience aliases at your disposal. They are intended for ease of use, so I encourage you to use them instead of the more complex way of creating loggers directly through the logger class. They are predefined with default configurations, so unless you need more special functionality, stick to using them.\
```basic_logger``` - configured with a standard log mechanism(forward logging) and a standard sink storage(dynamic storage), not thread-safe
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto logger = std::make_shared<lwlog::basic_logger<sinks::stdout_color_sink>>("CONSOLE"); // logger to stdout with default configuration
	
	return 0;
}
```
```console_color_logger``` - basic_logger with a colored sink to stdout\
```console_logger``` - basic_logger with an uncolored sink to stdout\
```file_logger``` - basic_logger with a file sink
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console_colored = std::make_shared<console_color_logger>("CONSOLE_COLORED");
	auto console_uncolored = std::make_shared<console_logger>("CONSOLE_UNCOLORED");
	auto file = std::make_shared<file_logger>("FILE", "C:/Users/user/Desktop/LogFolder/LOGS.txt");
	return 0;
}
```
```null_logger``` - A null logger is simply a logger with default configuration but without any sinks. Use it if you don't want compile time sinks and you are only interested in adding sinks later at runtime
```cpp
auto logger = std::make_shared<lwlog::null_logger>("LOGGER");
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
```default_log_policy``` - convenience alias for ```forward_log_policy```\
```forward_log_policy``` - your standard linear logging mechanism. You call a log function, and it's outputted to the specified sink\
```deferred_log_policy``` - as the name suggests, log calls are deffered for later use. When a log function is called, instead of directly sinking the data, it's stored in a storage for later use. This method provides very low latency, but use it only if you are sure you don't need your logs immediately\
```default_storage_policy``` - convenienve alias for ```static_storage_policy```\
```static_storage_policy``` - it configures the sink storage as an std::array - use it if you only set sinks in compile time and you know for sure you won't add sinks in at runtime, it is more lightweight than a dynamic sink storage\
```dynamic_storage_policy``` - it configures the sink storage as std::vector - use it if you may add sinks at runtime, or if you simply aren't sure if you are only going to use the compile-time set sinks\
```single_threaded_policy``` - configures the sinks with a placeholder mutex and locks - use it if you don't need thread-safety, it is more lightweight than thread-safe logger\
```multi_threaded_policy``` - configures the sinks with a mutex and locks for thread-safety
## Deferred logging
Deferred logging provides extremely low latency, however it's only applicable when you don't need the logs to be outputted imediately.\
The low latency comes from the fact that with deferred logging a log call doesn't sink and doesn't format anything, it only stores data. This data is sinked and formatted at a later stage, only when needed.
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
By calling sink_logs() you sink all the logs that are deferred for later use to their respective sinks with their respective patterns. If sink_logs() is called by a forward logging logger it will emit a warning.
## Thread-safety
Both the sinks and the logger classes expect a threading policy as a template parameter, which will determine whether they will be thread-safe or not.
However, if you want to use the convenienve aliases I meantioned above, you need to keep in mind they are not thread-safe. However, all of them have a thread-safe analog whith the same name and an _mt suffix.\
```basic_logger_mt```, ```console_color_logger_mt```, ```console_logger_mt```, ```file_logger_mt```, ```null_logger_mt```
