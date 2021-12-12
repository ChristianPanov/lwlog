#pragma once

#include "formatter.h"
#include "flag_data.h"

namespace lwlog::details
{
	struct date_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::date,
				datetime::get_date(log_msg.time_point)
			);
		}
	};

	struct date_short_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::date_short,
				datetime::get_date_short(log_msg.time_point)
			);
		}
	};

	struct year_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::year,
				datetime::get_year(log_msg.time_point)
			);
		}
	};

	struct year_short_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::year_short,
				datetime::get_year_short(log_msg.time_point)
			);
		}
	};

	struct month_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::month,
				datetime::get_month(log_msg.time_point)
			);
		}
	};

	struct month_name_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::month_name,
				datetime::get_month_name(log_msg.time_point)
			);
		}
	};

	struct month_name_short_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::month_name_short,
				datetime::get_month_name_short(log_msg.time_point)
			);
		}
	};

	struct day_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::day,
				datetime::get_day(log_msg.time_point)
			);
		}
	};

	struct weekday_name_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::weekday,
				datetime::get_weekday_name(log_msg.time_point)
			);
		}
	};

	struct weekday_name_short_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::weekday_short,
				datetime::get_weekday_name_short(log_msg.time_point)
			);
		}
	};

	struct time_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::time,
				datetime::get_time(log_msg.time_point)
			);
		}
	};

	struct hour_clock_24_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_clock_24,
				datetime::get_24_hour_clock(log_msg.time_point)
			);
		}
	};

	struct hour_clock_12_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_clock_12,
				datetime::get_12_hour_clock(log_msg.time_point)
			);
		}
	};

	struct ampm_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::ampm,
				datetime::get_ampm(log_msg.time_point)
			);
		}
	};

	struct hour_24_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_24,
				datetime::get_hour_24(log_msg.time_point)
			);
		}
	};

	struct hour_12_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_12,
				datetime::get_hour_12(log_msg.time_point)
			);
		}
	};

	struct minute_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::minute,
				datetime::get_minute(log_msg.time_point)
			);
		}
	};

	struct second_formatter : public formatter
	{
		void format(std::string& pattern, const log_message& log_msg) override
		{
			formatter::format_attribute(
				pattern,
				flag::second,
				datetime::get_second(log_msg.time_point)
			);
		}
	};
}