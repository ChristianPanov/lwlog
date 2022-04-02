#pragma once

namespace lwlog::details::flag
{
	static constexpr flag_pair logger_name	= { "{name}",			"%n" };
	static constexpr flag_pair level		= { "{level}",			"%l" };
	static constexpr flag_pair message		= { "{message}",		"%v" };
	static constexpr flag_pair thread_id	= { "{thread}",			"%t" };
	static constexpr flag_pair process_id	= { "{process}",		"%P" };
	static constexpr flag_pair line			= { "{line}",			"%#" };
	static constexpr flag_pair file			= { "{file}",			"%@" };
	static constexpr flag_pair function		= { "{func}",			"%!" };

	static constexpr flag_pair date				= { "{date}",				"%F" };
	static constexpr flag_pair date_short		= { "{date_short}",			"%D" };
	static constexpr flag_pair year				= { "{year}",				"%Y" };
	static constexpr flag_pair year_short		= { "{year_short}",			"%y" };
	static constexpr flag_pair month			= { "{month}",				"%m" };
	static constexpr flag_pair month_name		= { "{month_name}",			"%B" };
	static constexpr flag_pair month_name_short	= { "{month_name_short}",	"%b" };
	static constexpr flag_pair day				= { "{day}",				"%d" };
	static constexpr flag_pair weekday			= { "{weekday}",			"%A" };
	static constexpr flag_pair weekday_short	= { "{weekday_short}",		"%a" };
	static constexpr flag_pair time				= { "{time}",				"%T" };
	static constexpr flag_pair hour_clock_24	= { "{24_clock}",			"%R" };
	static constexpr flag_pair hour_clock_12	= { "{12_clock}",			"%r" };
	static constexpr flag_pair ampm				= { "{ampm}",				"%p" };
	static constexpr flag_pair hour_24			= { "{hour_24}",			"%H" };
	static constexpr flag_pair hour_12			= { "{hour_12}",			"%I" };
	static constexpr flag_pair minute			= { "{minute}",				"%M" };
	static constexpr flag_pair second			= { "{second}",				"%S" };
}