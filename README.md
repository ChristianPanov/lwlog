[![Codacy Badge](https://api.codacy.com/project/badge/Grade/05f2384593ed49bbaa51fa2516793d99)](https://app.codacy.com/gh/ChristianPanov/lwlog?utm_source=github.com&utm_medium=referral&utm_content=ChristianPanov/lwlog&utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/christianpanov/lwlog/badge)](https://www.codefactor.io/repository/github/christianpanov/lwlog)\
Very fast C++17 logging library
# Install
```
git clone --recursive https://github.com/ChristianPanov/lwlog
```
# The Most Important Question - Why Yet Another Logging Library?
_I will cut short on the speed or code simplicity that every other logging library boasts about, and will leave them for later.\
The actual importance of the library hides within its meaning to me. This library has served as an amazing journey.\
I started it when I knew very little about C++, let alone software engineering, and when I still made no distinction between writing reusable pieces of code and crafting libraries.\
I can say that I am proud of what I've made, for it has been a long journey comprised of not giving up and constantly daring to do the currently-impossible for me, according to my knowledge back then.\
As you will see later in the documentation, I do claim this library to be very fast and to have very clean code. I do claim to have designed it in a good way. However, even if that weren't objectively true, that would make no difference in the importance of this work to me, I would still be just as proud of it._

_No matter what you do or say, there will always be people who will hold a different view. It might always happen that you were in the wrong, or you could have done better. Anybody could take away the joy of your creation. However, no one can take away the hours you've spent crafting it, no one can take away the hours you've spent studying and learning in the process, no one can take away the times when you've felt like a god among men when you've faced the impossible, was stubborn enough to not give up, and actually did it. No one can take away any of that, any of the things which should make you proud. That's what real craftsmanship is - taking pride in what you do with all your heart and being too stubborn to give up on the currently-impossible._

# Design Highlights
- Clean and descriptive code
- Extremely fast synchronous logging (other logging libraries promise you speed by being asynchronous, which is not always a good idea, because it's hard to identify at what point the program crashed, causes more overhead and you can easily lose important messages, ***lwlog*** promises you both speed, as fast as synchronous logging can get, and keeping all your messages)
- High extensibility - [very easy to add your own types of sinks and loggers](https://github.com/ChristianPanov/lwlog#creating-your-own-sink)
- Very configurable - ***lwlog*** uses [policy classes](https://github.com/ChristianPanov/lwlog#logger-configuration) which you can just plug in based on your needs. At the same time, convenient easy-to-use predefined types([convenience aliases](https://github.com/ChristianPanov/lwlog#convenience-logger-aliases)) are made for the
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
- Log formatting according to a [custom user-defined pattern](https://github.com/ChristianPanov/lwlog#formatting)
- [Source metainformation attributes](https://github.com/ChristianPanov/lwlog/blob/master/README.md#source-metainformation-function-name-file-path-current-line)
- [Custom attributes](https://github.com/ChristianPanov/lwlog#custom-attributes)
- Global logger registry
# TODO (Temporary section)
- Binary logging
- Coloring based on log level
- Proper CMake to replace the Premake which is currently used
- Cross-platform colors
- Fmt-like formatting
- Meta-logging (also known as structured logging)
# Benchmarks
The benchmarks are still limited since there still aren't benchmarks for thread-safe logging, async logging, and loggers which sink to a file (they will be done)\
Benchmarked with picobench(https://github.com/iboB/picobench)
#### lwlog (stdout log, formatted, synchronous) vs spdlog (stdout log, formatted, synchronous)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.008 |     950 |      - |  1052631.6
             spdlog_bench |       8 |     0.403 |   50325 | 52.974 |    19870.8
            lwlog_bench * |      64 |     0.071 |    1107 |      - |   902679.8
             spdlog_bench |      64 |     3.232 |   50506 | 45.591 |    19799.5
            lwlog_bench * |     512 |     0.866 |    1691 |      - |   591019.3
             spdlog_bench |     512 |    34.119 |   66638 | 39.385 |    15006.3
            lwlog_bench * |    4096 |     5.150 |    1257 |      - |   795386.1
             spdlog_bench |    4096 |   311.846 |   76134 | 60.556 |    13134.7
            lwlog_bench * |    8192 |     7.365 |     898 |      - |  1112348.3
             spdlog_bench |    8192 |   610.478 |   74521 | 82.894 |    13419.0
===============================================================================
```
#### lwlog (stdout log, colored and formatted, synchronous) vs spdlog (stdout log, colored and formatted, synchronous)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.010 |    1262 |      - |   792079.2
             spdlog_bench |       8 |     1.875 |  234337 |185.614 |     4267.3
            lwlog_bench * |      64 |     0.078 |    1225 |      - |   816326.5
             spdlog_bench |      64 |    20.370 |  318275 |259.816 |     3141.9
            lwlog_bench * |     512 |     0.691 |    1348 |      - |   741384.3
             spdlog_bench |     512 |   592.973 | 1158149 |858.634 |      863.4
            lwlog_bench * |    4096 |     8.363 |    2041 |      - |   489788.1
             spdlog_bench |    4096 |  3186.113 |  777859 |380.986 |     1285.6
            lwlog_bench * |    8192 |     9.786 |    1194 |      - |   837148.5
             spdlog_bench |    8192 |  2384.691 |  291100 |243.694 |     3435.2
===============================================================================
```
#### lwlog (file log, formatted, synchronous) vs spdlog (file log, formatted, synchronous)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.001 |      75 |      - | 13333333.3
             spdlog_bench |       8 |     0.002 |     200 |  2.667 |  5000000.0
            lwlog_bench * |      64 |     0.004 |      68 |      - | 14545454.5
             spdlog_bench |      64 |     0.024 |     368 |  5.364 |  2711864.4
            lwlog_bench * |     512 |     0.034 |      67 |      - | 14883720.9
             spdlog_bench |     512 |     0.117 |     228 |  3.395 |  4383561.6
            lwlog_bench * |    4096 |     0.411 |     100 |      - |  9975645.4
             spdlog_bench |    4096 |     1.345 |     328 |  3.277 |  3044447.7
            lwlog_bench * |    8192 |     1.341 |     163 |      - |  6108874.0
             spdlog_bench |    8192 |     2.273 |     277 |  1.695 |  3604206.1
===============================================================================
```
#### lwlog (stdout log, forward(default) logging) vs lwlog (stdout log, deferred logging)
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
   lwlog_deferred_bench * |       8 |     0.001 |     100 |      - | 10000000.0
      lwlog_forward_bench |       8 |     0.010 |    1212 | 12.125 |   824742.3
   lwlog_deferred_bench * |      64 |     0.005 |      79 |      - | 12549019.6
      lwlog_forward_bench |      64 |     0.125 |    1956 | 24.549 |   511182.1
   lwlog_deferred_bench * |     512 |     0.050 |      97 |      - | 10240000.0
      lwlog_forward_bench |     512 |     0.662 |    1292 | 13.238 |   773530.7
   lwlog_deferred_bench * |    4096 |     0.423 |     103 |      - |  9674067.1
      lwlog_forward_bench |    4096 |     6.427 |    1569 | 15.179 |   637331.2
   lwlog_deferred_bench * |    8192 |     2.221 |     271 |      - |  3688262.6
      lwlog_forward_bench |    8192 |     9.877 |    1205 |  4.447 |   829443.6
===============================================================================
```
# Logical Architecture
```
Registry
└── Logger
    └── Sink
        └── Record
```
The architecture of ***lwlog*** is very simple, it's divided into three main modules - the **registry**, the **logger**, the **sinks**, and the **record**.
Module | Description
------------ | -------------
```Record``` | An object which holds the data which will eventually be logged, consisting of the message, level, metadata(current line, file, and function), timepoint, current thread ID, and current process ID
```Sink``` | An object which sends(sinks) data to an output destination. Usually, the data could be handled by a writer object, or you can directly handle the output in the ```sink_it()``` function, without using a writer. A sink uses two policy classes - ```lwlog::sink_color_policy``` and ```lwlog::threading_policy```
```Logger``` | An object which manages a number of sinks. It provides the same functionality as a sink, with the difference being that it contains a storage of sinks, and every operation the logger performs is distributed to all the sinks it contains. Also, it can distribute data to each sink in different ways. You can log either with the forward logging mechanism, or the deferred logging mechanism. The logging mechanism is handled by the ```lwog::log_policy``` policy class, where the ```sink_it()``` function of each sink is called. **NOTE**: I highly encourage using a logger, even when you are going to be using a single sink
```Registry``` | A global singleton class, which contains all the created loggers. It provides easy access to the created loggers from everywhere in your application. Each logger is registered in the registry on creation, unless automatic registry is turned off
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
			lwlog::sinks::stdout_sink
			>
		>("CONSOLE");
	
	console->set_level_filter(lwlog::level::info | lwlog::level::debug | lwlog::level::critical);
	console->set_pattern("[%T] [%n] [%l]: %v");
	console->critical("First critical message");
	
	return 0;
}
```
## Convenience logger aliases
In the file [***lwlog.h***](https://github.com/ChristianPanov/lwlog/blob/master/lwlog/src/lwlog.h) you can see several convenience aliases at your disposal.\
They are intended for ease of use, so I encourage you to use them instead of the more complex way of creating loggers directly through the logger class.\
They are predefined with default configurations, so unless you need more special functionality, stick to using them.
Alias | Description
------------ | -------------
```lwlog::basic_logger``` | Configured with a standard log mechanism(forward logging) and a standard sink storage(dynamic storage), not thread-safe
```lwlog::console_logger``` | basic_logger which sinks to stdout
```lwlog::file_logger``` | basic_logger which sinks to a file
```lwlog::null_logger``` | A null logger is simply a logger with default configuration but without any sinks. Use it if you don't want compile-time sinks and you are only interested in adding sinks later at runtime
#### Example
```cpp
#include "lwlog/lwlog.h"

int main()
{
	auto basic = std::make_shared<lwlog::basic_logger<lwlog::sinks::stdout_sink>>("CONSOLE");
	
	auto console = std::make_shared<lwlog::console_logger>("CONSOLE");
	auto file = std::make_shared<lwlog::file_logger>("FILE", "C:/Users/user/Desktop/LogFolder/LOGS.txt");
	
	auto null = std::make_shared<lwlog::null_logger>("LOGGER");
	
	return 0;
}
```
## Thread-safety
Both the sinks and the logger classes expect a threading policy as a template parameter, which will determine whether they will be thread-safe or not.
However, if you want to use the convenience aliases I mentioned above, you need to keep in mind they are not thread-safe.\
And for that reason, all of them have a thread-safe analog with the same name and an _mt suffix.\
```lwlog::basic_logger_mt```, ```lwlog::console_logger_mt```, ```lwlog::file_logger_mt```, ```lwlog::null_logger_mt```
## Logger configuration
Policy | Description
------------ | -------------
```lwlog::default_log_policy``` | Convenience alias for ```lwlog::forward_log_policy```
```lwlog::forward_log_policy``` | Your standard linear logging mechanism. You call a log function, and it's outputted to the specified sink
```lwlog::deferred_log_policy``` | As the name suggests, log calls are deferred for later use. When a log function is called, instead of directly sinking the data, it's stored in a storage for later use. This method provides very low latency but should be used only if you are sure you don't need your logs immediately
```lwlog::default_storage_policy``` | Convenience alias for ```lwlog::static_storage_policy```
```lwlog::static_storage_policy``` | Configures the sink storage as an ```std::array``` - use it if you only set sinks at compile time and you know for sure you won't add sinks at runtime, it is more lightweight than a dynamic sink storage
```lwlog::dynamic_storage_policy``` | Configures the sink storage as an ```std::vector``` - use it if you will add sinks at runtime, or if you simply aren't sure if you are only going to use the compile-time set sinks
```lwlog::single_threaded_policy``` | Configures the sinks with a placeholder mutex and locks - use it if you don't need thread-safety, it is more lightweight than a thread-safe logger
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
			lwlog::sinks::stdout_sink
			>
		>("CONSOLE");
	
	return 0;
}
```
## Deferred logging
Deferred logging provides extremely low latency, however, it's only applicable when you don't need the logs to be outputted immediately.\
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
			lwlog::sinks::stdout_sink
			>
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
The user can set a pattern, by which the log messages will be formatted. This pattern is internal to the library language, which is a sequence of formatting flags, alignment specifications(optional), characters, and color flags(optional). It allows flexibility in terms of configuring the output information in the most appropriate for the situation way, allowing as meaningful log output as possible.\
How is formatting done? - A pattern is set, and then it gets compiled by the library. Compilation is done in the ```lwlog::details::pattern``` class. It first parses the pattern and extracts the formatting flags, which are then used to retrieve only the formatters the pattern will need. It also parses the alignment specifications and extracts all the needed information for the alignments. In the end, all the retrieved formatters are called on the pattern and all formatting flags are replaced with their corresponding values and their corresponding alignment specifications(if any).
### Syntax
Verbose flag | Short flag | Description | Example
------------ | ------------- | ------------- | -------------
```{name}``` | ```%n``` | Logger's identification name | "logger name"
```{level}``` | ```%l``` | Log level of the message | "info", "warning", "error", "critical", "debug"
```{message}``` | ```%v``` | Log message | "Some log message"
```{thread}``` | ```%t``` | Thread id | "7592"
```{process}``` | ```%P``` | Process id | "22164"
```{line}``` | ```%#``` | Current line on which the log function is called | "84"
```{file}``` | ```%@``` | Path of the file in which the log function is called | "C:\Users\user\Desktop\lwlog\Sandbox\Sandbox.cpp"
```{func}``` | ```%!``` | Name of the function in which the log function is called | "main"
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
***lwlog*** gives you the ability to get source code metainformation in the form of attributes.\
One can get the current line on which the log function is called, the file path in which it is called, or the function name in which it is called, and all of that without macros.\
It is possible because of compiler intrinsics, which were first introduced in GCC, and now are also implemented in MSVC.\
***lwlog*** doesn't use C++20's ```std::source_location```, because I don't want to force users to use the new standard. Instead, the only requirement is to have a newer version of Visual Studio (>= 1927), which implements the needed intrinsics.\
If a newer version is not present, the metainformation flags will result into nothing.
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
	auto console = std::make_shared<lwlog::console_logger>("CONSOLE");
	console->set_pattern("[%T] [%n] [:^12%l]: %v");

	console->info("First info message");
	console->critical("First critical message");
	
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
Attribute - an object, which contains a pair of flags(verbose and shortened) and a value - each flag is replaced with its corresponding value.\
Custom attributes allow for flexible patterns - it represents a pair of flags and a reference to a value of a certain type.\
The value is an ```std::variant``` which contains a couple of reference types, to allow for more freedom in terms of having attribute values of different data types.
#### Example
```cpp
#include "lwlog/lwlog.h"

int main()
{
	std::string current_status = "inactive";
	
	auto console = std::make_shared<lwlog::console_logger>("CONSOLE");
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
Currently, an attribute can contain a reference to only a couple of types - ```int```, ```float```, ```double``` and ```std::string_view```.\
The reason for this is because more possible types in ```std::variant``` create more overhead, so I've tried to select the most probable types a user can use for values.
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
      			lwlog::sinks::file_sink
			>
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
	auto console_sink 	= std::make_shared<lwlog::sinks::stdout_sink<lwlog::single_threaded_policy>>();
	auto file_sink 		= std::make_shared<lwlog::sinks::file_sink<lwlog::single_threaded_policy>>("C:/Users/user/Desktop/LogFolder/LOGS.txt");
	lwlog::sink_list sinks 	= { console_sink, file_sink };

	auto logger_iterator 	= std::make_shared<lwlog::null_logger>("ITERATOR", sinks.begin(), sinks.end());
	auto logger_sink_list 	= std::make_shared<lwlog::null_logger>("SINK_LIST", sinks);
	auto logger_single_sink = std::make_shared<lwlog::null_logger>("SINGLE_SINK", console_sink);
	
	auto logger_combined = std::make_shared<
		lwlog::logger<
			lwlog::default_log_policy,
			lwlog::static_storage_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink
			>
		>("COMBINED", file_sink);

	return 0;
}
```
## Creating your own sink
As already mentioned, ***lwlog*** is extremely easy to extend. Let's give an example with sinks.\
To create your own sink, all you have to do is inherit from ```lwlog::sinks::sink``` and implement a ```sink_it()``` function, which takes a ```const details::record&```  as a parameter. That's it.
#### Example with an existing sink implementation
```cpp
namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class stdout_sink 
		: public sink<colored_policy, ThreadingPolicy>
		, private details::console_writer
	{
	private:
		using sink_t = sink<colored_policy, ThreadingPolicy>;
		
	public:
		stdout_sink();
		void sink_it(const details::record& record) override;
	};

	template<typename ThreadingPolicy>
	stdout_sink<ThreadingPolicy>::stdout_sink()
		: details::console_writer(stdout)
	{}

	template<typename ThreadingPolicy>
	void stdout_sink<ThreadingPolicy>::sink_it(const details::record& record)
	{
		details::console_writer::write(sink_t::m_pattern.compile(record));
	}
}
```
Here we inherit from the sink base class and configure it to be colored. Whether it's thread-safe or not is left up to the one using the sink.\
The color policy could be either colored(```lwlog::colored_policy```) or non-colored (```lwlog::uncolored_policy```).\
The non-colored policy will drop the color flags in the pattern instead of processing them, but will not ignore them. Using ```lwlog::colored_policy``` is most suitable for console sinks, since it relies on console-specific color codes.\
We only need the ```sink_it()``` function. It can do whatever you want it to do - write to console, write to file, write to file in some fancy way, write to another application, etc.\
Like in the example, you can either use some kind of a writer class, which handles the actual writing, or you can directly handle the writing in the function.\
The compiled and formatted message is received with ```sink_t::m_pattern.compile(record)```. We access the pattern member from the sink base class and then compile it with the log message.
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
		using sink_t = sink<colored_policy, ThreadingPolicy>;
	public:
		void sink_it(const details::record& record) override
		{
			// sink message to somewhere
		}
	};
}
```
## Default logger
The default logger is a logger object delivered to you by the library itself.\
It's not registered in the logger registry, it's global, it has default configuration and is NOT thread-safe, sinks to stdout.\
It's convenient if you just need the logging functionality, but don't want to create loggers by yourself. You can access it from everywhere in your application.\ Before using it, you need to call a function which initializes it.
```cpp
#include "lwlog/lwlog.h"

int main()
{
	lwlog::init_default_logger();
	
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
[22, 20:00:15] [info] [DEFAULT]: Info message
[22, 20:00:15] [warning] [DEFAULT]: Warning message
[22, 20:00:15] [error] [DEFAULT]: Error message
[22, 20:00:15] [critical] [DEFAULT]: Critical message
[22, 20:00:15] [debug] [DEFAULT]: Debug message
[20:00:15] [DEFAULT] [debug]: Will be displayed according to the new pattern
```
## Global operations
In order to apply a logger function to all loggers present in the registry, you can use the function ```lwlog::apply_to_all()``` in such manner
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
These directives use the default logger and are present in the [***lwlog.h***](https://github.com/ChristianPanov/lwlog/blob/master/lwlog/src/lwlog.h) file.\
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
	LWLOG_INIT_DEFAULT_LOGGER();
	LWLOG_SET_PATTERN("[%T] [%n] [%l]: %v");
	LWLOG_SET_LEVEL_FILTER(lwlog::level::error | lwlog::level::critical);
	LWLOG_ERROR("First error message");
	return 0;
}
```
# Tweakme
The [***tweakme.h***](https://github.com/ChristianPanov/lwlog/blob/master/lwlog/src/tweakme.h) file contains macros which serve the purpose of configurations.\
Depending on your needs, you can switch on and off certain features. Switching them off will completely remove them from the ***lwlog*** code which will increase performance and reduce overhead, because you shouldn't pay for what you don't need.
Macro | Off(0) - Default | On(1)
------------ | ------------- | -------------
```LWLOG_NO_TIME``` | Decreased performance. Has overhead of retrieving the system time and saving it in memory | Heavily increased performance. No overhead. Time flags will result into nothing
```LWLOG_USE_LOCALTIME``` | Time flags will result into local time | Time flags will result into UTC(GMT) time
```LWLOG_USE_THREAD_ID``` | Slightly increased performance. No overhead. ```{thread}``` or ```%t``` will result into nothing | Slightly decreased performance. Has overhead of retrieving the current thread id(tid) and saving it in memory
```LWLOG_USE_PROCESS_ID``` | Slightly increased performance. No overhead. ```{process}``` or  ```%P``` will result into nothing | Slightly decreased performance. Has overhead of retrieving the current process id(pid) and saving it in memory
# Performance
So how does ***lwlog*** achieve this performance? In the following section, I will break down all the performance-enhancing decisions that I've made.
### Formatting pattern
Formatting is usually the bottleneck in logging solutions and for that reason, it's usually handled on a background thread so it doesn't impede performance.\
However, because of ***lwlog***'s synchronous nature, we cannot take that route, and thus cannot take any liberties in how the compilation process of the pattern is done.\
The formatting pattern in question is parsed completely off the log call site, and all that's left for the log call functions is to do the replacement of the flags with their corresponding values. That way we do not burden every log call with doing the extra work of parsing the pattern every time, and it's parsed only once.\
The same goes for colors. They are only processed once right after the pattern flags are parsed.\
Pattern compilation process:
1. A pattern is set
2. The flags are parsed and only the needed formatters are created and pushed in a storage
3. The alignment specifications are parsed for all the needed information such as alignment side, width, and fill character
4. All color flags are processed 
5. When a log function is called, the formatters in the storage are called on the pattern with their appropriate alignment specifications
### Console output(stdout, stderr)
I/O in logging solutions is the second biggest, if not the biggest, performance bottleneck. Spewing data in the form of a human-readable medium(text) is heavy-duty.\
The best that could be done as of now, is manual buffering.\
With manual buffering, I manually increase the stream buffering with a size of ***2^22 bytes***, bigger than the default one(***512 bytes***), which improves the performance of output to stdout, stderr a lot.
```cpp
std::setvbuf(stdout, NULL, _IOFBF, 4194304);
std::fwrite("Hello, World!", 14, 1, stdout);
```
This example here shows how this is achieved. This is as fast as console output can get.
### Time
Time is handled in a special way. First off, since ```std::chrono``` is not as performant on Windows as it is on Linux, a platform-dependent approach, which proves to be much faster than its standard portable counterpart, is taken for Windows.\
It's taken even further. For some reason, getting the local time with ```std::chrono``` is faster than getting the UTC, and with the Windows API it's the opposite - getting the gmtime is faster than getting the UTC, so each implementation initially gets the faster of the two, and then arithmetically processes the time to the desired time format(either local time or UTC)
### Heuristics
For those of you who happen to not know, heuristics are logical shortcuts, approximate assumptions, which trade optimality, completeness, accuracy, or precision for speed.\
One example could be that ***lwlog*** does not use exception handling and performs almost no checks. That means that misusing the library could result in undefined behavior, memory leaks, or crashes. Fortunately, the design is simple enough to make it hard to misuse it, but all in all, it will not hold your hand if you do not use it properly.\
To further the example, ***lwlog*** assumes that the formatting pattern you've written is correct, with no syntax errors, so it doesn't perform any syntax checks which would impact the performance.\
These heuristics, which are present in almost any part of the library, benefit the performance greatly.\
**NOTE:** Every library could be misused, some more than others, but if we want speed, we as library crafters must take the responsibility to provide a simple enough interface, as straight-forward and as intuitive as possible, so the client would not misuse the library unless it's intentional.
