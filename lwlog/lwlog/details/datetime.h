#pragma once

#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>

namespace lwlog::details::datetime
{
	static std::string format_time(std::string format)
	{
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::gmtime(&in_time_t), format.data());
		return ss.str();
	}

	inline std::string get_time()					{ return format_time("%T"); }
	inline std::string get_date()					{ return format_time("%F"); }
	inline std::string get_date_short()				{ return format_time("%D"); }
	inline std::string get_second()					{ return format_time("%S"); }
	inline std::string get_minute()					{ return format_time("%M"); }
	inline std::string get_hour_24()				{ return format_time("%H"); }
	inline std::string get_hour_12()				{ return format_time("%I"); }
	inline std::string get_ampm()					{ return format_time("%p");	}	
	inline std::string get_12_hour_clock()			{ return format_time("%r"); }
	inline std::string get_24_hour_clock()			{ return format_time("%R"); }
	inline std::string get_weekday()				{ return format_time("%A"); }
	inline std::string get_weekday_abbreviated()	{ return format_time("%a"); }
	inline std::string get_day()					{ return format_time("%d"); }
	inline std::string get_month()					{ return format_time("%m"); }
	inline std::string get_month_name()				{ return format_time("%B"); }
	inline std::string get_month_name_abbreviated()	{ return format_time("%b"); }
	inline std::string get_year()					{ return format_time("%Y"); }
	inline std::string get_year_short()				{ return format_time("%y"); }
}