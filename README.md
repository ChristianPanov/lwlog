[![Codacy Badge](https://api.codacy.com/project/badge/Grade/05f2384593ed49bbaa51fa2516793d99)](https://app.codacy.com/gh/ChristianPanov/lwlog?utm_source=github.com&utm_medium=referral&utm_content=ChristianPanov/lwlog&utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/christianpanov/lwlog/badge)](https://www.codefactor.io/repository/github/christianpanov/lwlog)\
Very fast C++17 logging library
# Install
```
git clone --recursive https://github.com/ChristianPanov/lwlog
```
# The Most Important Question - Why Yet Another Logging Library?
_I will cut short on the speed or code simplicity that every other logging library boasts about and will leave them for later.\
The actual importance of the library lies within its meaning to me. This library has served as an amazing journey.\
I started it when I knew very little about C++, let alone software engineering, and when I still made no distinction between writing reusable pieces of code and crafting libraries.\
I can say that I am proud of what I've made, for it has been a long journey comprised of not giving up and constantly daring to do the currently-impossible for me, according to my knowledge back then.\
As you will see later in the documentation, I do claim this library to be very fast and to have very clean code. I do claim to have designed it in a good way. However, even if that weren't objectively true, that would make no difference in the importance of this work to me, I would still be just as proud of it._

_No matter what you do or say, there will always be people who hold a different view. It might always happen that you were in the wrong or that you could have done better. Anyone could take away the joy of your creation. However, no one can take away the hours you've spent crafting it, no one can take away the hours you've spent studying and learning in the process, no one can take away the times when you've felt like a god among men when you've faced the impossible, were stubborn enough not to give up, and actually did it. No one can take away any of that, any of the things that should make you proud. That's what real craftsmanship is - taking pride in what you do with all your heart and being too stubborn to give up on the currently-impossible._

# Design Highlights
- **Code Base:** The code is crafted with clarity, elegance, and readability in mind, hoping it is structured enough to prove relatively easy for developers to understand, modify, extend, and learn from.
- **Performance:** ***lwlog*** offers very fast logging capabilities, both in synchronous and asynchronous modes, ensuring minimal impact on your application’s performance.
- **Extensibility:** Adding new types of sinks and loggers is straightforward, providing flexibility to adapt the library to your specific needs. [Check out how to create your own sink for a practical example,](https://github.com/ChristianPanov/lwlog#creating-your-own-sink)
- **Configurability:** ***lwlog*** uses [policy classes](https://github.com/ChristianPanov/lwlog#logger-configuration) which you can just plug in based on your needs.
- **Ease of Use:** ***lwlog*** tries to follow a philosophy of intuitiveness. As the author, I am biased, so I can only hope the API is as intuitive as I see it in my eyes. Convenient easy-to-use predefined types([convenience aliases](https://github.com/ChristianPanov/lwlog#convenience-logger-aliases)) are made for simplicity without too much configuration. Most of the time, you will be just fine with using the predefined types.
# Features
- Written in modern C++17
- Very fast synchronous and asynchronous logging
- Forward(default, linear) and [deferred(non-linear)](https://github.com/ChristianPanov/lwlog#deferred-logging) logging mechanisms
- Verbosity levels
- Various log sinks
	- Console (stdout, stderr)
	- File
	- Custom sinks (it's extremely easy to add your own custom sinks)
- Support for both [compile-time](https://github.com/ChristianPanov/lwlog#multiple-sinks-compile-time) and [runtime](https://github.com/ChristianPanov/lwlog#multiple-sinks-runtime) sink configuration
- Custom sink configuration - each sink can have a unique log pattern and verbosity level
- Log formatting according to a [custom user-defined pattern](https://github.com/ChristianPanov/lwlog#formatting)
- [Source Metainformation Attributes](https://github.com/ChristianPanov/lwlog/blob/master/README.md#source-metainformation-function-name-file-path-current-line)
- [Custom Attributes](https://github.com/ChristianPanov/lwlog#custom-attributes)
- Global logger registry
# Benchmarks
Benchmarked with picobench(https://github.com/iboB/picobench)

**lwlog(*synchronous*)** *vs* **spdlog(*synchronous*)**
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.652 |   81512 |      - |    12268.1
             spdlog_bench |       8 |     4.844 |  605500 |  7.428 |     1651.5
            lwlog_bench * |      64 |     5.347 |   83540 |      - |    11970.2
             spdlog_bench |      64 |    46.576 |  727746 |  8.711 |     1374.1
            lwlog_bench * |     512 |    53.725 |  104931 |      - |     9530.1
             spdlog_bench |     512 |   135.479 |  264606 |  2.522 |     3779.2
            lwlog_bench * |    4096 |   451.722 |  110283 |      - |     9067.5
             spdlog_bench |    4096 |  1205.387 |  294283 |  2.668 |     3398.1
            lwlog_bench * |    8192 |   923.731 |  112760 |      - |     8868.4
             spdlog_bench |    8192 |  2334.964 |  285029 |  2.528 |     3508.4
===============================================================================
```
**lwlog(*synchronous, buffered*)** *vs* **spdlog(*synchronous*)**
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.016 |    2012 |      - |   496894.4
             spdlog_bench |       8 |     5.144 |  642950 |319.478 |     1555.3
            lwlog_bench * |      64 |     0.078 |    1218 |      - |   820512.8
             spdlog_bench |      64 |    19.179 |  299673 |245.886 |     3337.0
            lwlog_bench * |     512 |     0.629 |    1228 |      - |   813731.7
             spdlog_bench |     512 |   180.569 |  352673 |286.982 |     2835.5
            lwlog_bench * |    4096 |     4.961 |    1211 |      - |   825640.0
             spdlog_bench |    4096 |  1230.367 |  300382 |248.008 |     3329.1
            lwlog_bench * |    8192 |    11.767 |    1436 |      - |   696160.6
             spdlog_bench |    8192 |  2793.686 |  341026 |237.409 |     2932.3
===============================================================================
```
**lwlog(*asynchronous, blocking*)** *vs* **spdlog(*asynchronous, blocking*)**
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.000 |      50 |      - | 20000000.0
             spdlog_bench |       8 |     0.006 |     812 | 16.250 |  1230769.2
            lwlog_bench * |      64 |     0.002 |      34 |      - | 29090909.1
             spdlog_bench |      64 |     0.016 |     243 |  7.091 |  4102564.1
            lwlog_bench * |     512 |     0.017 |      33 |      - | 30295858.0
             spdlog_bench |     512 |     0.069 |     133 |  4.059 |  7463556.9
            lwlog_bench * |    4096 |     4.290 |    1047 |      - |   954756.3
             spdlog_bench |    4096 |  2316.282 |  565498 |539.913 |     1768.4
            lwlog_bench * |    8192 |     9.852 |    1202 |      - |   831481.0
             spdlog_bench |    8192 |  2050.576 |  250314 |208.132 |     3995.0
===============================================================================
```
**lwlog(*asynchronous, nonblocking*)** *vs* **spdlog(*asynchronous, nonblocking*)**
```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
            lwlog_bench * |       8 |     0.000 |      37 |      - | 26666666.7
             spdlog_bench |       8 |     0.006 |     775 | 20.667 |  1290322.6
            lwlog_bench * |      64 |     0.002 |      32 |      - | 30476190.5
             spdlog_bench |      64 |     0.028 |     434 | 13.238 |  2302158.3
            lwlog_bench * |     512 |     0.016 |      31 |      - | 32000000.0
             spdlog_bench |     512 |     0.103 |     201 |  6.438 |  4970873.8
            lwlog_bench * |    4096 |     0.180 |      43 |      - | 22730299.7
             spdlog_bench |    4096 |     0.673 |     164 |  3.737 |  6082566.1
            lwlog_bench * |    8192 |     0.426 |      52 |      - | 19230046.9
             spdlog_bench |    8192 |     1.036 |     126 |  2.431 |  7911154.0
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
```Record``` | An object that encapsulates the data that will be logged, including the message, logging level, metadata (current line, file, and function), timepoint, and execution context (current thread ID and process ID).
```Sink``` | An object that sends(sinks) data to an output destination. Usually, the data could be handled by a writer object, or you can directly handle the output in the ```sink_it()``` function without using a writer.
```Logger``` | An object that manages a number of sinks. It provides the same functionality as a sink, with the difference being that it contains a storage of sinks, and every operation the logger performs is distributed to all the sinks it contains. You can configure the logger to log synchronously or asynchronously. **NOTE**: I highly encourage using a logger, even when you are going to be using a single sink
```Registry``` | A global singleton class that acts as a repository for all created loggers, ensuring easy access throughout your application. Loggers are automatically registered upon creation unless automatic registration is disabled.
# Usage
## Basic Usage
```cpp
#include "lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::default_log_policy,
			lwlog::default_storage_policy,
			lwlog::default_flush_policy,
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
***lwlog.h*** simplifies the process of creating and configuring loggers through a set of convenient aliases at your disposal which you can find in the [***lwlog.h***](https://github.com/ChristianPanov/lwlog/blob/master/lwlog/src/lwlog.h) header file.
- **Ease of Use:** These aliases are intended for ease of use, simplifying the setup process, and offering straightforward access to logging functionalities. They are predefined with default configurations, making them ideal for general purposes.
- **Predefined Configurations:** The aliases come with predefined default settings, eliminating the need for extensive configuration in many use cases. This approach allows you to quickly integrate ***lwlog.h*** into your project and start logging with minimal setup.
- **Recommended Usage:** I recommend using these aliases for most of your logging needs, as they provide a balanced and simplified interface. However, if your project requires more specialized configurations or functionalities beyond the defaults, feel free to explore the more advanced options available through direct use of the logger class.
  
Alias | Description
------------ | -------------
```lwlog::basic_logger``` | Synchronous logger configured with standard flush policy, not thread-safe
```lwlog::console_logger``` | basic_logger which sinks to stdout
```lwlog::file_logger``` | basic_logger which sinks to a file
```lwlog::async_logger``` | Asynchronous logger configured with standard flush policy, not thread-safe
```lwlog::async_console_logger``` | async_logger which sinks to stdout
```lwlog::async_file_logger``` | async_logger which sinks to a file
#### Example
```cpp
#include "lwlog.h"

int main()
{
	auto basic = std::make_shared<lwlog::basic_logger<lwlog::sinks::stdout_sink>>("CONSOLE");
	
	auto console = std::make_shared<lwlog::console_logger>("CONSOLE");
	auto file = std::make_shared<lwlog::file_logger>("FILE", "C:/Users/user/Desktop/LogFolder/LOGS.txt");
	
	return 0;
}
```
## Thread-safety
Both the sinks and the logger classes expect a threading policy as a template parameter, which will determine whether they will be thread-safe or not.
However, if you want to use the convenience aliases mentioned above, you need to keep in mind they are not thread-safe.\
To facilitate ease of use while ensuring thread safety, ***lwlog.h*** offers thread-safe variants for all of its convenience aliases. These variants are distinguished by an ```_mt``` suffix in their names, indicating “multi-threaded” capability.\
## Logger configuration
Policy | Description
------------ | -------------
```lwlog::synchronous_policy``` | Your standard linear logging mechanism. You call a log function, and it's immediately processed and outputted to the specified sink. Works on a single thread, no background threads doing any processing
```lwlog::asynchronous_policy``` | As the name suggests, log calls are processed asynchronously, meaning they are handed off to a background thread to do the necessary operations on the log message and output it, allowing the originating thread to continue its execution in parallel
```lwlog::default_overflow_policy``` | Convenience alias for ```lwlog::blocking_overflow_policy```
```lwlog::blocking_overflow_policy``` | Configuration for the lwlog::asynchronous_policy class, on full queue the log operation enters a state of busy-wait, waiting for the queue to empty a slot for the new log message. It trades performance for safety, as no log messages will be lost in a high throughput environment where it's more likely to enqueue messages faster than they can be dequeued. However, performance decreases are minimal and are usually irrelevant
```lwlog::overwrite_last_overflow_policy``` | Configuration for the lwlog::asynchronous_policy class, on full queue the log operation overwrites the last message in the queue with the new one
```lwlog::discard_new_overflow_policy``` | Configuration for the lwlog::asynchronous_policy class, on full queue the log operation discards the new message
```lwlog::default_flush_policy``` | Convenience alias for ```lwlog::immediate_flush_policy```
```lwlog::buffered_flush_policy``` | Is functional only with stream sinks(stdout, stderr, file). Configures the sink with a manually increased buffer. Provides significant performance improvement, but messages are not flushed from the stream until the buffer is full, which could potentially lead to loss of data. It accepts a template parameter for the size of the buffer, by default it's **2^22 bytes**, bigger than the default one provided by the C++ specification(**512 bytes**)
```lwlog::immediate_flush_policy``` | Is functional only with stream sinks(stdout, stderr, file). Configures the sink with a flush function call after every log. Performance is not as good but is safer as all messages are flushed immediately on write, meaning no message could be potentially lost
```lwlog::single_threaded_policy``` | Configures the sinks with a placeholder mutex and locks - use it if you don't need thread-safety, it is more lightweight than a thread-safe logger
```lwlog::multi_threaded_policy``` | Configures the sinks with a mutex and locks for thread-safety
#### Example
```cpp
#include "lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::synchronous_policy,
			lwlog::default_flush_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink
			>
		>("CONSOLE");
	
	return 0;
}
```
## Asynchronous logging
The asynchronous logger works in a simple way. When a message is logged from the originating thread, it gets enqueued, awaiting processing by a dedicated worker thread running in the background. This worker thread is responsible for dequeuing messages, formatting them, and writing them to the configured sinks.
### Queue Concurrency Model
The core of the asynchronous logger is it's queue, which can operate based on two different concurrency models: *Single Producer Single Consumer (SPSC)* or *Multiple Producer Single Consumer (MPSC)*. The choice between the two models is based on whether the logger is configured to be thread-safe or not.
1. **Thread-Safe (MPSC Model):** When thread safety is enabled, implying the possibility of multiple threads producing log messages simultaneously, the queue operates based on the MPSC model. This ensures that all log messages are safely enqueued, even when multiple threads are involved.
2. **Non Thread-Safe(SPSC Model):** Conversely, when the logger is configured as non-thread-safe, indicating that log messages will only be produced by a single thread, the queue operates on the faster and lighter SPSC model.
### Configuration
The ```lwlog::asynchronous_policy``` structure expects two template parameters for configuration:
1. **Queue Capacity:** The maximum number of log messages the queue can hold. The default value is set to **1024**, which can also be accessed by the ```lwlog::default_async_queue_size``` global variable.
2. **Queue Overflow Policy:** Defines the behavior when the queue is full. The default policy is ```lwlog::block_overflow_policy```, which blocks the producing thread until space is available in the queue.
#### Example
```cpp
#include "lwlog.h"

int main()
{
	auto console = std::make_shared<
		lwlog::logger<
			lwlog::asynchronous_policy<
				lwlog::default_async_queue_size,
				lwlog::default_overflow_policy
			>,
			lwlog::default_flush_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink
			>
		>("CONSOLE");
	
	console->critical("First critical message");
	
	return 0;
}
```
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
```{topic}``` | ```%?``` | Name of the current topic | "topic name"
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
```{millisec}``` | ```%e``` | Millisecond part of the current second 000-999 | "829"
```{microsec}``` | ```%f``` | Microsecond part of the current second 000000-999999 | "830564"
```{nanosec}``` | ```%E``` | Nanosecond part of the current second 000000000-999999999 | "830564200"
### Source Metainformation (function name, file path, current line)
***lwlog*** offers the ability to integrate source code meta information as attributes in your logs, capturing details like the current line number, file path, and function name from the point where the log function is called.
- **Compiler Intrinsics:** This functionality is made possible through the use of compiler intrinsics, which were first introduced in GCC and are now supported by MSVC as well.
- **No Macros Needed:** Unlike other logging libraries, ***lwlog*** achieves this without the need for additional macros, resulting in cleaner and more straightforward code.
- **Version Requirements:** To utilize these features, a newer version of Visual Studio (version 1927 or later) is required, as it includes the necessary intrinsic implementations. If an older version is used, any metainformation flags in your log patterns will result in nothing.
- **Standard Compatibility:** While C++20 introduced std::source_location for similar purposes, ***lwlog*** does not mandate its usage. This design choice ensures broader compatibility, allowing users to benefit from source code meta information without being forced to adopt the latest C++ standard.
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
#include "lwlog.h"

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
#include "lwlog.h"

int main()
{
	auto console = std::make_shared<console_logger>("CONSOLE");
	console->set_pattern(".br_red([%T] [%n]) .green([%l]): .br_cyan(%v)");

	console->critical("First critical message");
	
	return 0;
}
```
### Level-based colors
You can also color your logs based on the severity level of the log with this flag - ```.level()```. Each severity level has a different color.
```cpp
#include "lwlog.h"

int main()
{
	auto console = std::make_shared<console_logger>("CONSOLE");
	console->set_pattern(".br_red([%T] [%n]) .level([%l]): .br_cyan(%v)");

	console->critical("First critical message");
	
	return 0;
}
```
## Custom attributes
Attributes serve as dynamic placeholders within log messages, providing a flexible way to include additional context or data. Each attribute consists of three main components:
1. **Flag:** A unique identifier for the attribute, used to denote its presence within the log pattern.
2. **Value:** A reference to the variable that holds the data to be logged. This can be any type of data that you wish to include in your log messages.
3. **Callback Function:** A function responsible for converting the attribute’s value to a string representation, ensuring it can be seamlessly incorporated into the log message. This function must always return a string.
### Default and Custom Callback Functions
- **Default Callback:** If no callback function is explicitly provided for an attribute, lwlog will utilize a default callback. This default function is capable of handling basic data types, including all arithmetic types and strings.
- **Custom Callback:** For more complex data types, specific formatting requirements, or if some operation on the value needs to be done, you can provide a custom callback function. This enables tailored string conversion to ensure your logged data appears exactly as you need it.

When a log message is being formatted, ***lwlog*** will identify instances of the attribute's flag within the log pattern. The callback function is then invoked with the attribute's value, and the resulting string replaces the flag in the log pattern.
```cpp
#include "lwlog.h"

int main()
{
	std::string current_status = "inactive";
	
	auto console = std::make_shared<lwlog::console_logger>("CONSOLE");
	console->add_attribute("{status}", current_status);
	console->set_pattern("{status} --- [%T] [%n] [%l]: %v");
	
	current_status = "active";
	console->info("First info message");
	
	return 0;
}
```
##### Output
```active --- [19:44:50] [CONSOLE] [info]: First info message```
## Multiple sinks (compile-time)
```cpp
#include "lwlog.h"

int main()
{
	auto logger = std::make_shared<
		lwlog::logger<
			lwlog::synchronous_policy,
			lwlog::default_flush_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink
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
#include "lwlog.h"

int main()
{
	auto console_sink 	= std::make_shared<lwlog::sinks::stdout_sink<lwlog::single_threaded_policy>>();
	auto file_sink 		= std::make_shared<lwlog::sinks::file_sink<lwlog::single_threaded_policy>>("C:/Users/user/Desktop/LogFolder/LOGS.txt");
	lwlog::sink_list sinks 	= { console_sink, file_sink };

	auto logger_iterator 	= std::make_shared<lwlog::basic_logger<>>("ITERATOR", sinks.begin(), sinks.end());
	auto logger_sink_list 	= std::make_shared<lwlog::basic_logger<>>("SINK_LIST", sinks);
	auto logger_single_sink = std::make_shared<lwlog::basic_logger<>>("SINGLE_SINK", console_sink);
	
	auto logger_combined = std::make_shared<
		lwlog::logger<
			lwlog::synchronous_policy,
			lwlog::default_flush_policy,
			lwlog::single_threaded_policy,
			lwlog::sinks::stdout_sink
			>
		>("COMBINED", file_sink);

	return 0;
}
```
## Creating your own sink
As already mentioned, ***lwlog*** is extremely easy to extend, making it straightforward to add your own custom sinks. Below, we walk through the process of creating a custom sink, using ```lwlog::sinks::stdout_sink``` as a practical example.
### Step 1: Inherit from the Base Sink Class
Begin by inheriting from ```lwlog::sinks::sink```, which serves as the base class for all sinks in ***lwlog***. Your custom sink class should also implement the ```sink_it()``` method, which is responsible for outputting the log message.
```cpp
namespace lwlog::sinks
{
	template<typename FlushPolicy, typename ThreadingPolicy>
	class stdout_sink 
		: public sink<true, ThreadingPolicy>
		, private details::stream_writer<FlushPolicy>
	{
		// ...
	};
}
```
In the example above, ```stdout_sink``` inherits from ```lwlog::sinks::sink``` and has two template parameters to handle the flush policy and the threading policy respectively.
### Step 2: Configure ANSI Color Support
The first template parameter for ```lwlog::sinks::sink``` indicates whether the sink supports ANSI colors. Set this to true for console sinks that utilize console-specific color codes. If set to false, the sink will ignore color flags in the pattern.
### Step 3: Implement the sink_it() Function
The ```sink_it()``` function is where your sink handles the log message. It receives a ```const details::record&```, representing the log message.
```cpp
template<typename FlushPolicy, typename ThreadingPolicy>
void stdout_sink<FlushPolicy, ThreadingPolicy>::sink_it(const details::record& record)
{
	m_current_level = record.level;
	details::stream_writer<FlushPolicy>::write(sink_t::m_pattern.compile(record));
}
```
In this function:
1. Set the current severity level to allow for level-based colors.
2. Compile the log message using the pattern.
3. Output the formatted message. You can utilize a writer class as shown in the example, or handle the writing directly within this function.
### Step 4: Handle Flushing (For Stream-Based Sinks)
If your sink is stream-based (e.g., writing to stdout, stderr, or a file), you should also consider a flushing policy. While the flush policy needs to be provided as part of the interface, it might not be applicable if your sink sends data in a non-stream-based manner.
### Full Example
```cpp
namespace lwlog::sinks
{
	template<typename FlushPolicy, typename ThreadingPolicy>
	class stdout_sink 
		: public sink<true, ThreadingPolicy>
		, private details::stream_writer<FlushPolicy>
	{
	private:
		using sink_t = sink<true, ThreadingPolicy>;
		
	public:
		stdout_sink();
		void sink_it(const details::record& record) override;
	};

	template<typename FlushPolicy, typename ThreadingPolicy>
	stdout_sink<FlushPolicy, ThreadingPolicy>::stdout_sink()
		: details::stream_writer<FlushPolicy>(stdout)
	{}

	template<typename FlushPolicy, typename ThreadingPolicy>
	void stdout_sink<FlushPolicy, ThreadingPolicy>::sink_it(const details::record& record)
	{
        	sink_t::m_current_level = record.level;
		details::stream_writer<FlushPolicy>::write(sink_t::m_pattern.compile(record));
	}
}
```
### Example for custom sink
```cpp
#include "sink.h"
#include "policy/sink_color_policy.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class new_custom_sink
		: public sink</*EnableAnsiColors*/, ThreadingPolicy>
	{
		using sink_t = sink</*EnableAnsiColors*/, ThreadingPolicy>;
	public:
		void sink_it(const details::record& record) override
		{
        		sink_t::m_current_level = record.level;
			// sink message to somewhere
		}
	};
}
```
## Default logger
***lwlog*** provides a globally accessible default logger, designed for convenience and ease of use.\
Here are some key points about this logger:
- **Pre-configured:** It's set up with a default configuration, eliminating the need for manual setup for simple logging tasks. It's synchronous.
- **Global Access:** It's a global logger, making it accessible from anywhere within your application.
- **Not Thread-safe:** It's important to note that this logger is **NOT** designed for concurrent multi-threaded logging. If thread safety is a requirement, consider creating a custom logger with the appropriate configuration.
- **Sink configuration:** By default, it sinks to stdout, making it suitable for console-based applications or debugging sessions.
- **Independent:** The default logger isn't registered in the logger registry. This means it operates independently of any other custom loggers you might set up.
  
Before you start using the default logger, it requires initialization through a specific function call. Once initialized, you can log messages without the need to manually create logger instances, which is particularly useful for small projects or for getting started quickly with ***lwlog***.
```cpp
#include "lwlog.h"

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
#include "lwlog.h"

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
#include "lwlog.h"

int main()
{
	auto console = std::make_shared<lwlog::console_logger>("CONSOLE");
	
	lwlog::get("CONSOLE")->critical("First critical message");
	
	return 0;
}
```
## Disabling logging
In most scenarios, you want to be able to disable logging entirely from your codebase. ***lwlog*** provides a flexible way to achieve this using preprocessor directives.
To turn off all logging function calls, define the ```LWLOG_DISABLE``` preprocessor directive at the top of your source file.
When ```LWLOG_DISABLE``` is defined, all logging calls expand to nothing.
```cpp
#define LWLOG_DISABLE
#define LWLOG_ERROR_OFF
#include "lwlog.h"

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
```LWLOG_NO_TIME``` | Decreased performance. Has overhead of retrieving the system time and saving it in memory | Increased performance. No overhead. Time flags will result into nothing
```LWLOG_USE_LOCALTIME``` | Time flags will result into local time | Time flags will result into UTC(GMT) time
```LWLOG_USE_PRECISE_UNITS``` | Slightly increased performance. No overhead. Precise time unit(microsecond, millisecond, nanosecond) flags result into nothing | Slightly decreased performance. Has overhead of retrieving needed data to calculate precise time units
```LWLOG_USE_THREAD_ID``` | Slightly increased performance. No overhead. ```{thread}``` or ```%t``` will result into nothing | Slightly decreased performance. Has overhead of retrieving the current thread id(tid) and saving it in memory
```LWLOG_USE_PROCESS_ID``` | Slightly increased performance. No overhead. ```{process}``` or  ```%P``` will result into nothing | Slightly decreased performance. Has overhead of retrieving the current process id(pid) and saving it in memory
# Performance
So how does ***lwlog*** achieve this performance? In the following section, I will break down all the performance-enhancing decisions that I've made.
### Asynchronous logging
Asynchronous logging is a very interesting topic because a lot of decisions need to be made and a lot of factors to be taken into account. For one, do we need a bounded or a dynamic queue, and what type of queue in terms of producer-consumer model.
Cache efficiency is a topic of its own and ensuring atomicity of operations is not exactly a trivial task. Let's look at how ***lwlog*** handles all of that.
#### Queue Concurrency Model
As mentioned before, ***lwlog*** takes a smart approach in implementing the queue, internally selecting between the *SPSC (Single Producer Single Consumer)* and *MPSC (Multiple Producer Single Consumer)* models based on the configured thread-safety of the logger. This automatic selection mechanism significantly cuts down unnecessary overhead while ensuring robust atomicity where it matters the most.
#### Cache Efficiency
The queue contains two atomic variables for the current write and read index, a very standard and straightforward detail of ring buffer implementations. However, that approach introduces the problem of false sharing when multiple threads read and modify them. False sharing occurs when variables are situated closely in memory, causing them to reside on the same cache line. This results in frequent and unnecessary cache invalidations, leading to suboptimal performance. To mitigate this, ***lwlog*** aligns the read and write indices to cache lines using **alignas(64)**, based on the assumption of a **64-byte** cache line size — a common characteristic of modern CPU architectures. This alignment ensures that these indices remain isolated from each other in terms of cache lines, effectively eliminating false sharing. The result is a more efficient utilization of the CPU cache, translating to enhanced overall performance.
```cpp
static constexpr auto cache_line_size{ std::hardware_destructive_interference_size };

alignas(cache_line_size) std::atomic_size_t m_write_index{};
alignas(cache_line_size) std::atomic_size_t m_read_index{};
```
### Pattern Formatting
Formatting tends to be a bottleneck in logging, since parsing and formatting imply a lot of consecutive searches and replaces in strings. Most of the time that cost is mitigated by simply handing it off to a background thread to do the processing. However, a smarter approach could be taken by analyzing what operations actually have to happen every time a log function is called and what operations could happen only once for the lifetime of the given pattern.\
Having that in mind, the formatting pattern is parsed only once, completely off the log call site. Log call functions are solely responsible for replacing the flags with their respective values, significantly reducing the workload on each log call. This design choice ensures that we are not parsing the pattern repetitively, a task that would otherwise impose additional performance overhead on every log action.\
Similarly, color flags are processed immediately after the pattern flags have been parsed, ensuring that this operation is performed just once and not repeated on every log call.
#### Pattern compilation process
Here is a step-by-step breakdown of the pattern compilation process, all that happens **OFF** the log call site:
1. **Set the Pattern:** The user defines the desired pattern.
2. **Parse Flags:** The flags within the pattern are parsed. Only the necessary formatters are instantiated and stored for future use.
3. **Alignment Specifications:** The alignment specifications for each formatter are parsed, capturing necessary details such as the alignment side, width, and fill character.
4. **Process Color Flags:** All color-related flags are parsed and replaced with their respective values(ANSI escape color codes).
   
When a log function is called, the stored formatters are invoked, applying the predetermined pattern and alignment specifications - simple string replacement which is optimized to invoke as few replaces as possible, to generate the final formatted log message. And that's the only thing that happens on the log call site.
### Console output(stdout, stderr)
I/O in logging solutions is the second biggest, if not the biggest, performance bottleneck. Spewing data in the form of a human-readable medium(text) is heavy-duty.\
A simple solution would be to increase the stream buffer size manually to avoid unnecessary flushes and provide a higher throughput.
```cpp
std::setvbuf(stdout, NULL, _IOFBF, 4194304);
std::fwrite("Hello, World!", 14, 1, stdout);
```
### Heuristics
Heuristics are logical shortcuts, approximate assumptions, that trade optimality, completeness, accuracy, or precision for speed. They provide a plausible and quicker solution rather than a guaranteed one. These educated guesses often eliminate the need for expensive computations, tapping into the power of implication and trend analysis to derive quick, plausible results. In practice, heuristics are like the seasoned intuition of an expert, cutting through the noise and focusing on what truly matters to make swift decisions.
