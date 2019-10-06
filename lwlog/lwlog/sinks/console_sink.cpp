#include "console_sink.h"

#include "../formatter.h"
#include "../print.h"

namespace lwlog::sinks
{
	void console_sink::sink_it(std::string_view message, level log_level)
	{
		if (static_cast<std::underlying_type_t<level>>(m_level)
			& static_cast<std::underlying_type_t<level>>(log_level))
		{
			lwlog::print("{0} \n", message.data());
		}
	}
}