#pragma once

#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>

namespace lwlog::details::datetime
{
	static std::string _format_time(std::string format)
	{
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::gmtime(&in_time_t), format.data());
		return ss.str();
	}

	inline std::string get_time()					{ return _format_time("%T"); }
	inline std::string get_date()					{ return _format_time("%F"); }
	inline std::string get_date_short()				{ return _format_time("%D"); }
	inline std::string get_second()					{ return _format_time("%S"); }
	inline std::string get_minute()					{ return _format_time("%M"); }
	inline std::string get_hour_24()				{ return _format_time("%H"); }
	inline std::string get_hour_12()				{ return _format_time("%I"); }
	inline std::string get_ampm()					{ return _format_time("%p"); }	
	inline std::string get_12_hour_clock()			{ return _format_time("%r"); }
	inline std::string get_24_hour_clock()			{ return _format_time("%R"); }
	inline std::string get_weekday()				{ return _format_time("%A"); }
	inline std::string get_weekday_abbreviated()	{ return _format_time("%a"); }
	inline std::string get_day()					{ return _format_time("%d"); }
	inline std::string get_month()					{ return _format_time("%m"); }
	inline std::string get_month_name()				{ return _format_time("%B"); }
	inline std::string get_month_name_abbreviated()	{ return _format_time("%b"); }
	inline std::string get_year()					{ return _format_time("%Y"); }
	inline std::string get_year_short()				{ return _format_time("%y"); }
}