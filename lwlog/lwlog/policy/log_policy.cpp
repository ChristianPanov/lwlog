#include "log_policy.h"

#include "details/formatter/formatter.h"

namespace lwlog
{
	void forward_log_policy::log(primitives::sink_ptr sink, std::string_view message, level t_level)
	{
		sink->sink_it(details::formatter::format(sink->pattern()));
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

	void deferred_log_policy::log(primitives::sink_ptr sink, std::string_view message, level t_level)
	{
		storage.push_back({ sink, message.data(), sink->pattern(), t_level });
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