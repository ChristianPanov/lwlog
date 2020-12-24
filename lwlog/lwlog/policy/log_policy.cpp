#include "log_policy.h"

#include "details/formatter/formatter.h"

namespace lwlog
{
	void forward_log_policy::log(primitives::sink_ptr t_sink, std::string_view message, level t_level)
	{
		t_sink->sink_it(details::formatter::format(t_sink->pattern()));
	}

	void forward_log_policy::init_attributes(std::string_view message, level t_level)
	{
		details::formatter::insert_pattern_data({
			{"{message}",		"%v",	message.data()},
			{"^level_color^",	"",		level_details::color_value(t_level)},
			{"{log_level}",		"%l",	level_details::to_string(t_level)},
			{"{log_level_abr}",	"%L",	std::string(1, level_details::to_string(t_level)[0])}
			});
	}

	void deferred_log_policy::log(primitives::sink_ptr t_sink, std::string_view t_message, level t_level)
	{
		storage.push_back({ t_sink, t_message.data(), t_sink->pattern(), t_level });
	}

	void deferred_log_policy::sink_logs()
	{
		for (const auto& [sink, message, pattern, level] : storage)
		{
			details::formatter::insert_pattern_data({
				{"{message}",		"%v",	message},
				{"^level_color^",	"",		level_details::color_value(level)},
				{"{log_level}",		"%l",	level_details::to_string(level)},
				{"{log_level_abr}",	"%L",	std::string(1, level_details::to_string(level)[0])}
				});
			sink->sink_it(details::formatter::format(pattern));
		}
	}
}
