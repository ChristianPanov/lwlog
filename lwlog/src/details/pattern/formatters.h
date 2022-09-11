#pragma once

#include "formatter.h"
#include "flag_data.h"
#include "level.h"

namespace lwlog::details
{
	struct level_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::level,
				level_details::to_string(record.level)
			);
		}
	};

	struct message_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::message,
				record.message
			);
		}
	};

	struct thread_id_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::thread_id,
				record.thread_id
			);
		}
	};

	struct process_id_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::process_id,
				record.process_id
			);
		}
	};

	struct line_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::line,
				record.meta.line()
			);
		}
	};

	struct file_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::file,
				record.meta.file_name()
			);
		}
	};

	struct function_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::function,
				record.meta.function_name()
			);
		}
	};

	struct date_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::date,
				datetime::get_date(record.time_point)
			);
		}
	};

	struct date_short_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::date_short,
				datetime::get_date_short(record.time_point)
			);
		}
	};

	struct year_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::year,
				datetime::get_year(record.time_point)
			);
		}
	};

	struct year_short_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::year_short,
				datetime::get_year_short(record.time_point)
			);
		}
	};

	struct month_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::month,
				datetime::get_month(record.time_point)
			);
		}
	};

	struct month_name_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::month_name,
				datetime::get_month_name(record.time_point)
			);
		}
	};

	struct month_name_short_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::month_name_short,
				datetime::get_month_name_short(record.time_point)
			);
		}
	};

	struct day_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::day,
				datetime::get_day(record.time_point)
			);
		}
	};

	struct weekday_name_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::weekday,
				datetime::get_weekday_name(record.time_point)
			);
		}
	};

	struct weekday_name_short_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::weekday_short,
				datetime::get_weekday_name_short(record.time_point)
			);
		}
	};

	struct time_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::time,
				datetime::get_time(record.time_point)
			);
		}
	};

	struct hour_clock_24_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_clock_24,
				datetime::get_24_hour_clock(record.time_point)
			);
		}
	};

	struct hour_clock_12_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_clock_12,
				datetime::get_12_hour_clock(record.time_point)
			);
		}
	};

	struct ampm_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::ampm,
				datetime::get_ampm(record.time_point)
			);
		}
	};

	struct hour_24_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_24,
				datetime::get_hour_24(record.time_point)
			);
		}
	};

	struct hour_12_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_12,
				datetime::get_hour_12(record.time_point)
			);
		}
	};

	struct minute_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::minute,
				datetime::get_minute(record.time_point)
			);
		}
	};

	struct second_formatter : public formatter
	{
		void format(std::string& pattern, const record& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::second,
				datetime::get_second(record.time_point)
			);
		}
	};
}