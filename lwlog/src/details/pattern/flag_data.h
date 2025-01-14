#pragma once

#include "attribute.h"

namespace lwlog::details::flag
{
	inline constexpr flag_pair level		{ "{level}",		"%l" };
	inline constexpr flag_pair message		{ "{message}",		"%v" };
	inline constexpr flag_pair thread_id	{ "{thread}",		"%t" };
	inline constexpr flag_pair process_id	{ "{process}",		"%P" };
	inline constexpr flag_pair line			{ "{line}",			"%#" };
	inline constexpr flag_pair file			{ "{file}",			"%@" };
	inline constexpr flag_pair function		{ "{func}",			"%!" };
	inline constexpr flag_pair topic		{ "{topic}",		"%." };
	inline constexpr flag_pair full_topic	{ "{full_topic}",	"%," };

	inline constexpr flag_pair date				{ "{date}",				"%F" };
	inline constexpr flag_pair date_short		{ "{date_short}",		"%D" };
	inline constexpr flag_pair year				{ "{year}",				"%Y" };
	inline constexpr flag_pair year_short		{ "{year_short}",		"%y" };
	inline constexpr flag_pair month			{ "{month}",			"%m" };
	inline constexpr flag_pair month_name		{ "{month_name}",		"%B" };
	inline constexpr flag_pair month_name_short	{ "{month_name_short}",	"%b" };
	inline constexpr flag_pair day				{ "{day}",				"%d" };
	inline constexpr flag_pair weekday			{ "{weekday}",			"%A" };
	inline constexpr flag_pair weekday_short	{ "{weekday_short}",	"%a" };
	inline constexpr flag_pair time				{ "{time}",				"%T" };
	inline constexpr flag_pair hour_clock_24	{ "{24_clock}",			"%R" };
	inline constexpr flag_pair hour_clock_12	{ "{12_clock}",			"%r" };
	inline constexpr flag_pair ampm				{ "{ampm}",				"%p" };
	inline constexpr flag_pair hour_24			{ "{hour_24}",			"%H" };
	inline constexpr flag_pair hour_12			{ "{hour_12}",			"%I" };
	inline constexpr flag_pair minute			{ "{minute}",			"%M" };
	inline constexpr flag_pair second			{ "{second}",			"%S" };
	inline constexpr flag_pair millisecond		{ "{millisec}",			"%e" };
	inline constexpr flag_pair microsecond		{ "{microsec}",			"%f" };
	inline constexpr flag_pair nanosecond		{ "{nanosec}",			"%E" };
}