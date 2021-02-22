#pragma once

namespace lwlog::details::flag
{
	static flag_pair logger_name	= { "{name}",			"%n" };
	static flag_pair level			= { "{level}",			"%l" };
	static flag_pair message		= { "{message}",		"%v" };
	static flag_pair thread_id		= { "{thread}",			"%t" };
	static flag_pair level_color	= { "{level_color}",	"%c" };

	static flag_pair date				= { "{date}",				"%F" };
	static flag_pair date_short			= { "{date_short}",			"%D" };
	static flag_pair year				= { "{year}",				"%Y" };
	static flag_pair year_short			= { "{year_short}",			"%y" };
	static flag_pair month				= { "{month}",				"%m" };
	static flag_pair month_name			= { "{month_name}",			"%B" };
	static flag_pair month_name_short	= { "{month_name_short}",	"%b" };
	static flag_pair day				= { "{day}",				"%d" };
	static flag_pair weekday			= { "{weekday}",			"%A" };
	static flag_pair weekday_short		= { "{weekday_short}",		"%a" };
	static flag_pair time				= { "{time}",				"%T" };
	static flag_pair hour_clock_24		= { "{24_clock}",			"%R" };
	static flag_pair hour_clock_12		= { "{12_clock}",			"%r" };
	static flag_pair ampm				= { "{ampm}",				"%p" };
	static flag_pair hour_24			= { "{hour_24}",			"%H" };
	static flag_pair hour_12			= { "{hour_12}",			"%I" };
	static flag_pair minute				= { "{minute}",				"%M" };
	static flag_pair second				= { "{second}",				"%S" };
}