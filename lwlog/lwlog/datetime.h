#pragma once

#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

namespace lwlog::datetime
{
	static std::string get_chrono(std::string format)
	{
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::localtime(&in_time_t), format.c_str());
		return ss.str();
	}

	static std::string get_time()					{ return get_chrono("%H:%M:%S"); }
	static std::string get_date()					{ return get_chrono("%Y-%m-%d"); }
	static std::string get_date_short()				{ return get_chrono("%m/%d/%y"); }
	static std::string get_second()					{ return get_chrono("%S"); }
	static std::string get_minute()					{ return get_chrono("%M"); }
	static std::string get_hour_24()				{ return get_chrono("%H"); }
	static std::string get_hour_12()				{ return get_chrono("%I"); }
	static std::string get_weekday()				{ return get_chrono("%A"); }
	static std::string get_weekday_abbreviated()	{ return get_chrono("%a"); }
	static std::string get_day()					{ return get_chrono("%d"); }
	static std::string get_month()					{ return get_chrono("%m"); }
	static std::string get_month_name()				{ return get_chrono("%B"); }
	static std::string get_month_name_abbreviated() { return get_chrono("%b"); }
	static std::string get_year()					{ return get_chrono("%Y"); }
	static std::string get_year_short()				{ return get_chrono("%y"); }
}