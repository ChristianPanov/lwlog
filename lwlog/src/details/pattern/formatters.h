#pragma once

#include "formatter.h"
#include "flag_data.h"
#include "level.h"
#include "details/topic.h"

namespace lwlog::details
{
	struct level_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::level,
				level_details::to_string(record.log_level)
			);
		}
	};

	struct message_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
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
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::thread_id,
				record.exec_context().thread_id()
			);
		}
	};

	struct process_id_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::process_id,
				record.exec_context().process_id()
			);
		}
	};

	struct line_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
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
		void format(std::string& pattern, const record_base& record) const override
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
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::function,
				record.meta.function_name()
			);
		}
	};

	struct topic_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::topic,
				details::topic_registry::current_topic()
			);
		}
	};

	struct date_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::date,
				os::datetime::get_date(record.time_point)
			);
		}
	};

	struct date_short_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::date_short,
				os::datetime::get_date_short(record.time_point)
			);
		}
	};

	struct year_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::year,
				os::datetime::get_year(record.time_point)
			);
		}
	};

	struct year_short_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::year_short,
				os::datetime::get_year_short(record.time_point)
			);
		}
	};

	struct month_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::month,
				os::datetime::get_month(record.time_point)
			);
		}
	};

	struct month_name_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::month_name,
				os::datetime::get_month_name(record.time_point)
			);
		}
	};

	struct month_name_short_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::month_name_short,
				os::datetime::get_month_name_short(record.time_point)
			);
		}
	};

	struct day_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::day,
				os::datetime::get_day(record.time_point)
			);
		}
	};

	struct weekday_name_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::weekday,
				os::datetime::get_weekday_name(record.time_point)
			);
		}
	};

	struct weekday_name_short_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::weekday_short,
				os::datetime::get_weekday_name_short(record.time_point)
			);
		}
	};

	struct time_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::time,
				os::datetime::get_time(record.time_point)
			);
		}
	};

	struct hour_clock_24_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_clock_24,
				os::datetime::get_24_hour_clock(record.time_point)
			);
		}
	};

	struct hour_clock_12_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_clock_12,
				os::datetime::get_12_hour_clock(record.time_point)
			);
		}
	};

	struct ampm_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::ampm,
				os::datetime::get_ampm(record.time_point)
			);
		}
	};

	struct hour_24_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_24,
				os::datetime::get_hour_24(record.time_point)
			);
		}
	};

	struct hour_12_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::hour_12,
				os::datetime::get_hour_12(record.time_point)
			);
		}
	};

	struct minute_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::minute,
				os::datetime::get_minute(record.time_point)
			);
		}
	};

	struct second_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::second,
				os::datetime::get_second(record.time_point)
			);
		}
	};

	struct millisecond_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::millisecond,
				os::datetime::get_millisecond(record.time_point)
			);
		}
	};

	struct microsecond_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::microsecond,
				os::datetime::get_microsecond(record.time_point)
			);
		}
	};

	struct nanosecond_formatter : public formatter
	{
		void format(std::string& pattern, const record_base& record) const override
		{
			formatter::format_attribute(
				pattern,
				flag::nanosecond,
				os::datetime::get_nanosecond(record.time_point)
			);
		}
	};
}