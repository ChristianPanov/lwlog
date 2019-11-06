#include "console_sink.h"

#include "../formatter.h"
#include "../print.h"

namespace lwlog::sinks
{
	void console_sink::sink_it(std::string_view message, level log_level)
	{
		lwlog::print("{0} \n", message.data());
	}
}