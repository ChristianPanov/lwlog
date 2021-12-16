#pragma once

#include "logger_formatters.h"
#include "datetime_formatters.h"

namespace lwlog::details
{
	std::unordered_map<std::string_view, std::shared_ptr<formatter>> verbose_logger_data
	{
		{flag::logger_name.verbose,		std::make_shared<logger_name_formatter>()},
		{flag::level.verbose,			std::make_shared<level_formatter>()},
		{flag::message.verbose,			std::make_shared<message_formatter>()},
		{flag::thread_id.verbose,		std::make_shared<thread_id_formatter>()},
		{flag::line.verbose,			std::make_shared<line_formatter>()},
		{flag::file.verbose,			std::make_shared<file_formatter>()},
		{flag::function.verbose,		std::make_shared<function_formatter>()}
	};

	std::unordered_map<std::string_view, std::shared_ptr<formatter>> shortened_logger_data
	{
		{flag::logger_name.shortened,	std::make_shared<logger_name_formatter>()},
		{flag::level.shortened,			std::make_shared<level_formatter>()},
		{flag::message.shortened,		std::make_shared<message_formatter>()},
		{flag::thread_id.shortened,		std::make_shared<thread_id_formatter>()},
		{flag::line.shortened,			std::make_shared<line_formatter>()},
		{flag::file.shortened,			std::make_shared<file_formatter>()},
		{flag::function.shortened,		std::make_shared<function_formatter>()}
	};

	std::unordered_map<std::string_view, std::shared_ptr<formatter>> verbose_datetime_data
	{
		{flag::date.verbose,				std::make_shared<date_formatter>()},
		{flag::date_short.verbose,			std::make_shared<date_short_formatter>()},
		{flag::year.verbose,				std::make_shared<year_formatter>()},
		{flag::year_short.verbose,			std::make_shared<year_short_formatter>()},
		{flag::month.verbose,				std::make_shared<month_formatter>()},
		{flag::month_name.verbose,			std::make_shared<month_name_formatter>()},
		{flag::month_name_short.verbose,	std::make_shared<month_name_short_formatter>()},
		{flag::day.verbose,					std::make_shared<day_formatter>()},
		{flag::weekday.verbose,				std::make_shared<weekday_name_formatter>()},
		{flag::weekday_short.verbose,		std::make_shared<weekday_name_short_formatter>()},
		{flag::time.verbose,				std::make_shared<time_formatter>()},
		{flag::hour_clock_24.verbose,		std::make_shared<hour_clock_24_formatter>()},
		{flag::hour_clock_12.verbose,		std::make_shared<hour_clock_12_formatter>()},
		{flag::ampm.verbose,				std::make_shared<ampm_formatter>()},
		{flag::hour_24.verbose,				std::make_shared<hour_24_formatter>()},
		{flag::hour_12.verbose,				std::make_shared<hour_12_formatter>()},
		{flag::minute.verbose,				std::make_shared<minute_formatter>()},
		{flag::second.verbose,				std::make_shared<second_formatter>()}
	};

	std::unordered_map<std::string_view, std::shared_ptr<formatter>> shortened_datetime_data
	{
		{flag::date.shortened,				std::make_shared<date_formatter>()},
		{flag::date_short.shortened,		std::make_shared<date_short_formatter>()},
		{flag::year.shortened,				std::make_shared<year_formatter>()},
		{flag::year_short.shortened,		std::make_shared<year_short_formatter>()},
		{flag::month.shortened,				std::make_shared<month_formatter>()},
		{flag::month_name.shortened,		std::make_shared<month_name_formatter>()},
		{flag::month_name_short.shortened,	std::make_shared<month_name_short_formatter>()},
		{flag::day.shortened,				std::make_shared<day_formatter>()},
		{flag::weekday.shortened,			std::make_shared<weekday_name_formatter>()},
		{flag::weekday_short.shortened,		std::make_shared<weekday_name_short_formatter>()},
		{flag::time.shortened,				std::make_shared<time_formatter>()},
		{flag::hour_clock_24.shortened,		std::make_shared<hour_clock_24_formatter>()},
		{flag::hour_clock_12.shortened,		std::make_shared<hour_clock_12_formatter>()},
		{flag::ampm.shortened,				std::make_shared<ampm_formatter>()},
		{flag::hour_24.shortened,			std::make_shared<hour_24_formatter>()},
		{flag::hour_12.shortened,			std::make_shared<hour_12_formatter>()},
		{flag::minute.shortened,			std::make_shared<minute_formatter>()},
		{flag::second.shortened,			std::make_shared<second_formatter>()}
	};
}