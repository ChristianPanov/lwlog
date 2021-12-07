[![Codacy Badge](https://api.codacy.com/project/badge/Grade/05f2384593ed49bbaa51fa2516793d99)](https://app.codacy.com/gh/ChristianPanov/lwlog?utm_source=github.com&utm_medium=referral&utm_content=ChristianPanov/lwlog&utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/christianpanov/lwlog/badge)](https://www.codefactor.io/repository/github/christianpanov/lwlog)\
Very fast C++17 logging library
# Install
```
git clone --recursive https://github.com/ChristianPanov/lwlog
```
# Design Highlights
- Clean and descriptive code
- Extremely fast synchronous logging (other logging libraries promise you speed by being asycnrhonous, which is not always a good idea, because it's hard to identify at what point the program crashed, causes more overhead and you can easily lose important messages, lwlog promises you both speed, as fast as synchronous logging can get, and keeping all your messages)
- High extensibility - [very easy to add your own types of sinks and loggers](https://github.com/ChristianPanov/lwlog#creating-your-own-sink)
- Very configurable - lwlog uses [policy classes](https://github.com/ChristianPanov/lwlog#logger-configuration) which you can just plug in based on your needs. At the same time, convenient easy-to-use predefined types([convenience aliases](https://github.com/ChristianPanov/lwlog#convenience-logger-aliases)) are made for the
people who want simplicity without too much configuration. Most of the time you will be just fine with using the predefined types
# Features
- Written in modern C++17
- Very fast synchronous logging
- Forward(default, linear) and [deferred(non-linear)](https://github.com/ChristianPanov/lwlog#deferred-logging) logging mechanisms
- Verbosity levels
- Various log sinks
	- Console (stdout, stderr)
	- File
	- Custom sinks (it's extremely easy to add your own custom sinks)
- Support for both [compile-time](https://github.com/ChristianPanov/lwlog#multiple-sinks-compile-time) and [runtime](https://github.com/ChristianPanov/lwlog#multiple-sinks-runtime) sink configuration
- Custom sink configuration - each sink can have a unique log pattern and verbosity level
- Log formatting according to a custom user-defined pattern
- [Source metainformation attributes](https://github.com/ChristianPanov/lwlog/blob/master/README.md#source-metainformation-function-name-file-path-current-line)
- [Custom attributes](https://github.com/ChristianPanov/lwlog#custom-attributes)
- Global logger registry
# To be implemented
- Cross-platform colors
- Fmt-like formatting
- Meta-logging (also known as structured logging)
# Benchmarks
The benchmarks are still limited, since there still arent benchmarks for thread-safe logging, async logging, and loggers which sink to a file (they will be done)\
Benchmarked with picobench(https://github.com/iboB/picobench)
#### lwlog (formatted, synchronous) vs spdlog (formatted, synchronous)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.012 |    1450 |      - |   689655.2
             spdlog_bench |       8 |     0.447 |   55912 | 38.560 |    17885.1
            lwlog_bench * |      64 |     0.057 |     889 |      - |  1124780.3
             spdlog_bench |      64 |     3.687 |   57610 | 64.800 |    17357.8
            lwlog_bench * |     512 |     0.450 |     879 |      - |  1137272.3
             spdlog_bench |     512 |    36.991 |   72248 | 82.166 |    13841.2
            lwlog_bench * |    4096 |     3.944 |     962 |      - |  1038513.2
             spdlog_bench |    4096 |   317.930 |   77619 | 80.609 |    12883.4
            lwlog_bench * |    8192 |     6.893 |     841 |      - |  1188452.1
             spdlog_bench |    8192 |   648.315 |   79140 | 94.054 |    12635.8
===============================================================================
```
#### lwlog (colored and formatted, synchronous) vs spdlog (colored and formatted, synchronous)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.012 |    1537 |      - |   650406.5
             spdlog_bench |       8 |     1.927 |  240850 |156.650 |     4152.0
            lwlog_bench * |      64 |     0.058 |     904 |      - |  1105354.1
             spdlog_bench |      64 |    16.164 |  252556 |279.164 |     3959.5
            lwlog_bench * |     512 |     0.720 |    1406 |      - |   711209.9
             spdlog_bench |     512 |   142.256 |  277842 |197.605 |     3599.2
            lwlog_bench * |    4096 |     5.702 |    1392 |      - |   718369.6
             spdlog_bench |    4096 |  1135.223 |  277154 |199.099 |     3608.1
            lwlog_bench * |    8192 |     6.763 |     825 |      - |  1211260.9
             spdlog_bench |    8192 |  2225.977 |  271725 |329.131 |     3680.2
===============================================================================
```
#### lwlog (forward(default) logging) vs lwlog (deferred logging)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
   lwlog_deferred_bench * |       8 |     0.003 |     375 |      - |  2666666.7
      lwlog_forward_bench |       8 |     0.010 |    1200 |  3.200 |   833333.3
   lwlog_deferred_bench * |      64 |     0.024 |     376 |      - |  2655601.7
      lwlog_forward_bench |      64 |     0.050 |     778 |  2.066 |  1285140.6
   lwlog_deferred_bench * |     512 |     0.171 |     334 |      - |  2990654.2
      lwlog_forward_bench |     512 |     0.356 |     694 |  2.077 |  1439820.0
   lwlog_deferred_bench * |    4096 |     1.086 |     265 |      - |  3771986.4
      lwlog_forward_bench |    4096 |     3.124 |     762 |  2.877 |  1311265.5
   lwlog_deferred_bench * |    8192 |     2.034 |     248 |      - |  4028522.3
      lwlog_forward_bench |    8192 |     6.122 |     747 |  3.011 |  1338146.7
===============================================================================
```
# Logical Architecture
```
Registry
└── Logger
    └── Sink
        └── Writer(optional)
```
The architecture of lwlog is very simple, it's divided into three main modules - the **registry**, the **logger**, and the **sinks**.\
An optional fourth part is the **_writer_**.
Module | Description
------------ | -------------
```Writer``` | Abstraction which outputs the data to the destination. It is optional, because it is not actually needed, and there is no strict specification for what a writer should be
```Sink``` | An object which sends(sinks) data to an output destination. Usually, the data could be handled by a writer object, or you can directly handle the output in the ```sink_it()``` function, without using a writer. A sink uses two policy classes - ```lwlog::sink_color_policy``` and ```lwlog::threading_policy```
```Logger``` | An object, which manages a number of sinks. It provides the same functionality as a sink, with the difference being that it contains a storage of sinks, and every operation the logger performs is distributed to all the sinks it contains. Also it can distribute data to each sink in different ways. You can log either with the forward logging mechanism, or the deferred logging mechanism. The logging mechanism are handled by the ```lwog::log_policy``` policy class, where the ```sink_it()``` function of each sink is called. **NOTE**: I highly encourage using a logger, even when you are going to be using a single sink
```Registry``` | A global singleton class, which contains all the created loggers. It provides an easy access to the created loggers from everywhere in your application. Each logger is registered in the registry on creation, unless ```automatic_registry()``` is turned off
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
	
	console->set_level_filter(lwlog::level::info | lwlog::level::debug | lwlog::level::critical);
	console->set_pattern("[%T] [%n] [%l]: %v");
	console->critical("First critical message");
	
	return 0;
}
```
## Convenience logger aliases
In the file lwlog.h you can see several convenience aliases at your disposal.\
They are intended for ease of use, so I encourage you to use them instead of the more complex way of creating loggers directly through the logger class.\
They are predefined with default configurations, so unless you need more special functionality, stick to using them.
Alias | Description
------------ | -------------
```lwlog::basic_logger``` | Configured with a standard log mechanism(forward logging) and a standard sink storage(dynamic storage), not thread-safe
```lwlog::console_logger``` | basic_logger which sinks to stdout
```lwlog::file_logger``` | basic_logger which sinks to a file
```lwlog::null_logger``` | A null logger is simply a logger with default configuration but without any sinks. Use it if you don't want compile time sinks and you are only interested in adding sinks later at runtime
#### Example
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto basic = std::make_shared<lwlog::basic_logger<sinks::stdout_sink>>("CONSOLE");
	
	auto console = std::make_shared<console_logger>("CONSOLE");
	auto file = std::make_shared<file_logger>("FILE", "C:/Users/user/Desktop/LogFolder/LOGS.txt");
	
	auto null = std::make_shared<lwlog::null_logger>("LOGGER");
	
	return 0;
}
```
## Thread-safety
Both the sinks and the logger classes expect a threading policy as a template parameter, which will determine whether they will be thread-safe or not.
However, if you want to use the convenienve aliases I meantioned above, you need to keep in mind they are not thread-safe.\
And for that reason all of them have a thread-safe analog whith the same name and an _mt suffix.\
```lwlog::basic_logger_mt```, ```lwlog::console_logger_mt```, ```lwlog::file_logger_mt```, ```lwlog::null_logger_mt```
## Logger configuration
Policy | Description
------------ | -------------
```lwlog::default_log_policy``` | Convenience alias for ```forward_log_policy```
```lwlog::forward_log_policy``` | Your standard linear logging mechanism. You call a log function, and it's outputted to the specified sink
```lwlog::deferred_log_policy``` | As the name suggests, log calls are deffered for later use. When a log function is called, instead of directly sinking the data, it's stored in a storage for later use. This method provides very low latency, but should be used only if you are sure you don't need your logs immediately
```lwlog::default_storage_policy``` | Convenienve alias for ```static_storage_policy```
```lwlog::static_storage_policy``` | Configures the sink storage as an std::array - use it if you only set sinks in compile time and you know for sure you won't add sinks at runtime, it is more lightweight than a dynamic sink storage
```lwlog::dynamic_storage_policy``` | Configures the sink storage as std::vector - use it if you may add sinks at runtime, or if you simply aren't sure if you are only going to use the compile-time set sinks
```lwlog::single_threaded_policy``` | Configures the sinks with a placeholder mutex and locks - use it if you don't need thread-safety, it is more lightweight than thread-safe logger
```lwlog::multi_threaded_policy``` | Configures the sinks with a mutex and locks for thread-safety
#### Example
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
## Deferred logging
Deferred logging provides extremely low latency, however it's only applicable when you don't need the logs to be outputted immediately.\
The low latency comes from the fact that with deferred logging a log call doesn't sink and doesn't format anything, it only stores data.\
This data is sent to a sink and formatted at a later stage, only when needed.
There is one problem with it - all log information will be lost if there is an application crash and you haven't sinked the deferred logs.
#### Example
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
## Formatting
Formatting is handled with a pay for what you need approach.\
The user is able to set a pattern, by which the log messages will be formatted. This pattern is an internal to the library language, which is a sequence of formatting flags, alignment specifications(optional), characters and color flags(optional). It allows flexibility in terms of configuring the output information in the most appropriate for the situation way, allowing as meaningful log output as possible.\
How is formatting done? - A pattern is set, and then it gets compiled by the library. Compilation is done in the ```lwlog::details::pattern``` class. It first parses the pattern, and extracts the formatting flags, which are then used to retrieve only the formatters the pattern will need. It also parses the alignment specifications and extracts all the needed information for the alignments. In the end, all the retrieved formatters are called on the pattern and all formatting flags are replaced with their corresponding values and their corresponding alignment specifications(if any).
### Syntax
Verbose flag | Short flag | Description | Example
------------ | ------------- | ------------- | -------------
```{name}``` | ```%n``` | Logger's identification name | "logger name"
```{level}``` | ```%l``` | Log level of the message | "info", "warning", "error", "critical", "debug"
```{message}``` | ```%v``` | Log message | "Some log message"
```{thread}``` | ```%t``` | Thread id | "6567358443629571051"
```{line}``` | ```%#``` | Current line on which the log function is called | "84"
```{file}``` | ```%@``` | Path of the file in which the log function is called | "C:\Users\user\Desktop\lwlog\Sandbox\Sandbox.cpp"
```{func}``` | ```%!``` | Name of the function in which the log function is called | "main"
```{thread}``` | ```%t``` | Thread id | "6567358443629571051"
```{date}``` | ```%F``` | Current date YY-MM-DD | "2021-01-01"
```{date_short}``` | ```%D``` | Current short date MM/DD/YY | "01/01/21"
```{year}``` | ```%Y``` | Current year | "2021"
```{year_short}``` | ```%y``` | Current short year | "21"
```{month}``` | ```%m``` | Current month 01-12 | "01"
```{month_name}``` | ```%B``` | Current month as name | "January"
```{month_name_short}``` | ```%b``` | Current short month as name | "Jan"
```{day}``` | ```%d``` | Current day of month 01-31 | "01"
```{weekday}``` | ```%A``` | Current day of the week as name | "Friday"
```{weekday_short}``` | ```%a``` | Current short day of the week as name | "Fri"
```{time}``` | ```%T``` | Current time HH:MM:SS | "17:42:10"
```{24_clock}``` | ```%R``` | Current 24-hour format time | "17:42"
```{12_clock}``` | ```%r``` | Current 12-hour format time | "05:42:10pm"
```{ampm}``` | ```%p``` | am/pm | "am", "pm"
```{hour_24}``` | ```%H``` | Current hour in 24-hour format | "17"
```{hour_12}``` | ```%I``` | Current hour in 12-hour format | "05"
```{minute}``` | ```%m``` | Current minute 00-59 | "42"
```{second}``` | ```%s``` | Current second 00-59 | "10"
### Source metainformation (function name, file path, current line)
lwlog gives you the ability to get source code metainformation in the form of attributes. One can get the current line on which the log function is called, the file path in which it is called, or the function name in which it is called, and all of that without macros.\
It is possible because of compiler intrinsics, which were first introduced in GCC, and now they are also implemented in MSVC. lwlog doesn't use c++20's std::source_location, because I don't want to force users to use the new standard. Instead, the only requirement is to have a newer version of Visual Studio (>= 1927), which implements the needed intrinsics.
### Alignment Syntax
Alignment specifications are individual to an attribute, and they contain an alignment side, width, and an optional fill character, which by default, if not specified, is an empty space.

Syntax | Example | Result
------------ | ------------- | -------------
```:<<width><flag>``` | ```[:<12%l]``` | "[info&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;]"
```:><width><flag>``` | ```[:>12%l]``` | "[&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;info]"
```:^<width><flag>``` | ```[:^12%l]``` | "[&nbsp;&nbsp;&nbsp;&nbsp;info&nbsp;&nbsp;&nbsp;&nbsp;]"
```:^<fill_character><width><flag>``` | ```[:^-12%l]``` | "[----info----]"
#### Example
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<console_logger>("CONSOLE");
	console->set_pattern("[%T] [%n] [:^12%l]: %v");

	console->info("First info message");
	console->critical("First info message");
	
	return 0;
}
```
##### Output
```
[19:44:50] [CONSOLE] [    info    ]: First info message
[19:44:50] [CONSOLE] [  critical  ]: First critical message
```
### Color Flags
Color flags are used for coloring a pattern. Each color flag is scoped.
Foreground Color Flag | Bright Foreground Color Flag
------------ | -------------
```.black()``` | ```.br_black()```
```.red()``` | ```.br_red()```
```.green()``` | ```.br_green()```
```.yellow()``` | ```.br_yellow()```
```.blue()``` |```.br_blue()```
```.magenta()``` | ```.br_magenta()```
```.cyan()``` | ```.br_cyan()```
```.white()``` | ```.br_white()```

Background Color Flag | Bright Background Color Flag
------------ | -------------
```.bg_black()``` | ```.br_bg_black()```
```.bg_red()``` | ```.br_bg_red()```
```.bg_green()``` | ```.br_bg_green()```
```.bg_yellow()``` | ```.br_bg_yellow()```
```.bg_blue()``` | ```.br_bg_blue()```
```.bg_magenta()``` | ```.br_bg_magenta()```
```.bg_cyan()``` | ```.br_bg_cyan()```
```.bg_white()``` | ```.br_bg_white()```
#### Example
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto console = std::make_shared<console_logger>("CONSOLE");
	console->set_pattern(".br_red([%T] [%n]) .green([%l]): .br_cyan(%v)");

	console->critical("First critical message");
	
	return 0;
}
```
## Custom attributes
Attribute - an object, which contains a pair of flags(verbose and shortened) and a value - each flag is replaced with it's corresponding value.
Custom attributes allow for flexible patterns. A custom attribute represents a pair of flags and a reference to a value of a certain type.
A custom attribute's value is an std::variant which contains a couple of reference types, to allow for more freedom in terms of having attribute values of different data types.
#### Example
```cpp
#include "lwlog/lwlog.h"

int main()
{
	std::string current_status = "inactive";
	
	auto console = std::make_shared<console_logger>("CONSOLE");
	console->add_attribute({"{status}", "%s"}, current_status);
	console->set_pattern("{status} --- [%T] [%n] [%l]: %v");
	
	current_status = "active";
	console->info("First info message");
	
	return 0;
}
```
##### Output
```active --- [19:44:50] [CONSOLE] [info]: First critical message```
#### Limitations
Currently, an attribute can contain a reference to only a couple of types - int, float, double and std::string.\
The reason for this is because more possible types in std::variant creates more overhead, so I've tried to select the most probable types a user can use for values.
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
	logger->set_pattern("[%T] [%n] [%l]: %v");
	// Log message will be distributed to both sinks
	logger->critical("First critical message");
	
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
	lwlog::sink_list sinks = { console_sink, file_sink };

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
## Creating your own sink
As I said and promissed, lwlog is extremely easy to extend. Let's give an example with sinks.\
To create your own sink, all you have to do is inherit from ```lwlog::sinks::sink``` and implement a ```sink_it()``` function. That's it.
#### Example with an existing sink implementation
```cpp
namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stdout_sink 
		: public sink<colored_policy, ThreadingPolicy>
		, public details::stream_writer
	{
	public:
		stdout_sink();
		void sink_it(const details::log_message& log_msg) override;
	};

	template<typename ThreadingPolicy>
	stdout_sink<ThreadingPolicy>::stdout_sink()
		: details::stream_writer(stdout)
	{}

	template<typename ThreadingPolicy>
	void stdout_sink<ThreadingPolicy>::sink_it(const details::log_message& log_msg)
	{
		details::stream_writer::write(m_pattern.compile(log_msg));
	}
}
```
Here we inherit from the sink base class, and configure it to be colored. Whether it's thread-safe or not is left up to the one using the sink.\
The color policy could be either colored(```lwlog::colored_policy```) or non-colored (```lwlog::uncolored_policy```).\
The non-colored policy will drop the color flags in the pattern instead of processing them, but will not ignore them. Using ```lwlog::colored_policy``` is most suitable for console sinks, since it relies on console specific color codes.\
We only need the ```sink_it()``` function, which is called as the actual log call. It can do whatever you want it to do - write to console, write to file, write to file in some fancy way, write to another application, etc.\
As mentioned in [Logical Architecture](https://github.com/ChristianPanov/lwlog#logical-architecture), you can either use some kind of a writer class, which handles the actual writing, or you can directly handle the writing in the function.\
The compiled and formatted message is recieved with ```m_pattern.compile(log_msg)```. We access the pattern member from the sink base class and then compile it with the log message.
#### Example
```cpp
#include "sink.h"
#include "policy/sink_color_policy.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class new_custom_sink
		: public sink<colored_policy, ThreadingPolicy>
	{
	public:
		void sink_it(const details::log_message& log_msg) override
		{
			// sink message to somewhere
		}
	};
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

	lwlog::set_level_filter(lwlog::level::debug | lwlog::level::critical);
	lwlog::info("Will not be displayed");

	lwlog::set_pattern("[%T] [%n] [%l]: %v");
	lwlog::debug("Will be displayed according to the new pattern");

	return 0;
}
```
##### Output
```
[22, 20:00:15] [info] [GLOBAL]: Info message
[22, 20:00:15] [warning] [GLOBAL]: Warning message
[22, 20:00:15] [error] [GLOBAL]: Error message
[22, 20:00:15] [critical] [GLOBAL]: Critical message
[22, 20:00:15] [debug] [GLOBAL]: Debug message
[20:00:15] [GLOBAL] [debug]: Will be displayed according to the new pattern
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
	lwlog::apply_to_all([](lwlog::logger_ptr logger)
		{
			logger->set_pattern("[%T] [%n] [%l]: %v");
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
## Switching off logging
If you want to be able to turn off logging completely, you can use the preprocessor directives.
These directives use the default loggger and are present in the **_lwlog.h_** file.\
They will log unless you disable logging with ```LWLOG_DISABLE```(should always be at the very top of the file), or you switch off a specific logging level.\
Levels can be switched off at runtime as well, just by using the ```LWLOG_SET_LEVEL_FILTER``` directive.\
If logging is disabled, the directives expand to nothing.
#### Example
```cpp
#define LWLOG_DISABLE
#define LWLOG_ERROR_OFF
#include "lwlog/lwlog.h"

int main()
{
	LWLOG_SET_PATTERN("[%T] [%n] [%l]: %v");
	LWLOG_SET_LEVEL_FILTER(lwlog::level::error | lwlog::level::critical);
	LWLOG_ERROR("First error message");
	return 0;
}
```
# Performance
So how does lwlog achieve this performance? The answer lies in one very important architectural decision and a couple of techniques.
### Architecture
The architectural decision that speeds up the performance is about how the formatting pattern compilation is handled. The pattern in question is parsed completely off the log call site, and all that's left for the log call functions is to do the replacement of the flags with their corresponding values.\
Color processing is also done off the log call site. Color processing can be a big performance bottleneck, and it doesn't need to happen at the log call site, since colors have nothing to do with the current log information. Once the pattern is set, it immediately processes all the color flags in place.
1. A pattern is set
2. All color flags are processed 
3. The pattern is parsed and only the needed formatters are pushed to a storage
4. The alignment specifications are parsed and all the needed information such as alignment side, width, and fill character is extracted
5. When a log function is called, the formatters in the storage are called on the pattern with their appropriate alignment specifications
### Output
A very important performance improvement, probably the biggest one, is manual buffering.\
With manual buffering, I manually increase the stream buffering with a size of **_2^22 bytes_**, bigger than the default one(**_512 bytes_**), which improves the performance of output to stdout, stderr and a file a lot.
```cpp
std::setvbuf(stdout, NULL, _IOFBF, size);
std::fwrite("Hello, World!", 14, 1, stdout);
```
This example here shows how this is achieved. This is as fast as console output can get.
### Time
Time is handled in a special way. First off, since std::chrono is not as performant on Windows as it is on Linux, a platform-dependant approach, which is much faster than std::chrono is, is taken for Windows.\
Still, I take it even further. For some reason, getting the local time with std::chrono is faster than getting the UTC, and with the Windows API it's the opposite - getting the gmtime is faster than getting the UTC, so each implementation initially gets the faster of the two, and then arithmetically processes the time to the desired time format(either local time or UTC)
