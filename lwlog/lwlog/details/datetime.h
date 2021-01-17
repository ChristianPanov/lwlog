#pragma once

#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>

namespace lwlog::details::datetime
{
	static std::string format_time(const char* format)
	{
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::localtime(&in_time_t), format);
		return ss.str();
	}

	static std::string get_time()					{ return format_time("%T"); }
	static std::string get_date()					{ return format_time("%F"); }
	static std::string get_date_short()				{ return format_time("%D"); }
	static std::string get_second()					{ return format_time("%S"); }
	static std::string get_minute()					{ return format_time("%M"); }
	static std::string get_hour_24()				{ return format_time("%H"); }
	static std::string get_hour_12()				{ return format_time("%I"); }
	static std::string get_ampm()					{ return format_time("%p"); }	
	static std::string get_12_hour_clock()			{ return format_time("%r"); }
	static std::string get_24_hour_clock()			{ return format_time("%R"); }
	static std::string get_weekday()				{ return format_time("%A"); }
	static std::string get_weekday_abbreviated()	{ return format_time("%a"); }
	static std::string get_day()					{ return format_time("%d"); }
	static std::string get_month()					{ return format_time("%m"); }
	static std::string get_month_name()				{ return format_time("%B"); }
	static std::string get_month_name_abbreviated()	{ return format_time("%b"); }
	static std::string get_year()					{ return format_time("%Y"); }
	static std::string get_year_short()				{ return format_time("%y"); }
}