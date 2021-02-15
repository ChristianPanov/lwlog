#pragma once

namespace lwlog::details::flag
{
	struct flag_pair
	{
		std::string_view verbose;
		std::string_view shortened;
	};

	flag_pair logger_name	= { "{name}",			"%n" };
	flag_pair level			= { "{level}",			"%l" };
	flag_pair message		= { "{message}",		"%v" };
	flag_pair thread_id		= { "{thread}",			"%t" };
	flag_pair level_color	= { "{level_color}",	"%c" };

	flag_pair date				= { "{date}",				"%F" };
	flag_pair date_short		= { "{date_short}",			"%D" };
	flag_pair year				= { "{year}",				"%Y" };
	flag_pair year_short		= { "{year_short}",			"%y" };
	flag_pair month				= { "{month}",				"%m" };
	flag_pair month_name		= { "{month_name}",			"%B" };
	flag_pair month_name_short	= { "{month_name_short}",	"%b" };
	flag_pair day				= { "{day}",				"%d" };
	flag_pair weekday			= { "{weekday}",			"%A" };
	flag_pair weekday_short		= { "{weekday_short}",		"%a" };
	flag_pair time				= { "{time}",				"%T" };
	flag_pair hour_clock_24		= { "{24_clock}",			"%R" };
	flag_pair hour_clock_12		= { "{12_clock}",			"%r" };
	flag_pair ampm				= { "{ampm}",				"%p" };
	flag_pair hour_24			= { "{hour_24}",			"%H" };
	flag_pair hour_12			= { "{hour_12}",			"%I" };
	flag_pair minute			= { "{minute}",				"%M" };
	flag_pair second			= { "{second}",				"%S" };
}