#include "console_sink.h"
#include "../details/formatter.h"
#include "../details/print.h"

#include <iostream>

namespace lwlog::sinks
{
	void console_sink::sink_it(std::string_view message)
	{
		std::cout << message << '\n';
	}
}