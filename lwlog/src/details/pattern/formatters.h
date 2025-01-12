#pragma once

#include "formatter.h"
#include "flag_data.h"
#include "level.h"

namespace lwlog::details
{
	struct level_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			formatter::format_attribute(
				dst,
				flag::level,
				level_details::to_string(record.log_level)
			);
		}
	};

	struct message_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			formatter::format_attribute(
				dst,
				flag::message,
				record.message_buffer.data()
			);
		}
	};

	struct thread_id_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			formatter::format_attribute(
				dst,
				flag::thread_id,
				record.exec_context().thread_id()
			);
		}
	};

	struct process_id_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			formatter::format_attribute(
				dst,
				flag::process_id,
				record.exec_context().process_id()
			);
		}
	};

	struct line_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			formatter::format_attribute(
				dst,
				flag::line,
				record.meta.line()
			);
		}
	};

	struct file_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			formatter::format_attribute(
				dst,
				flag::file,
				record.meta.file_name()
			);
		}
	};

	struct function_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			formatter::format_attribute(
				dst,
				flag::function,
				record.meta.function_name()
			);
		}
	};

	struct topic_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			formatter::format_attribute(
				dst,
				flag::topic,
				record.get_topic_registry().current_topic()
			);
		}
	};

	struct full_topic_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			formatter::format_attribute(
				dst,
				flag::full_topic,
				record.get_topic_registry().full_topic()
			);
		}
	};

	struct date_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::date,
				os::datetime::ensure_two_digit_format(time_point.year)
					+ '-' + os::datetime::ensure_two_digit_format(time_point.month)
					+ '-' + os::datetime::ensure_two_digit_format(time_point.day)
			);
		}
	};

	struct date_short_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::date_short,
				os::datetime::ensure_two_digit_format(time_point.month) 
					+ '/' + os::datetime::ensure_two_digit_format(time_point.day) 
					+ '/'+ os::datetime::ensure_two_digit_format(time_point.year % 100)
			);
		}
	};

	struct year_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::year,
				os::datetime::ensure_two_digit_format(time_point.year)
			);
		}
	};

	struct year_short_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::year_short,
				os::datetime::ensure_two_digit_format(time_point.year % 100)
			);
		}
	};

	struct month_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::month,
				os::datetime::ensure_two_digit_format(time_point.month)
			);
		}
	};

	struct month_name_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::month_name,
				os::datetime::month_name[time_point.month]
			);
		}
	};

	struct month_name_short_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::month_name_short,
				os::datetime::month_name_short[time_point.month]
			);
		}
	};

	struct day_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::day,
				os::datetime::ensure_two_digit_format(time_point.day)
			);
		}
	};

	struct weekday_name_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::weekday,
				os::datetime::weekday_name[time_point.weekday]
			);
		}
	};

	struct weekday_name_short_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::weekday_short,
				os::datetime::weekday_name_short[time_point.weekday]
			);
		}
	};

	struct time_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::time,
				os::datetime::ensure_two_digit_format(time_point.hour)
					+ ':' + os::datetime::ensure_two_digit_format(time_point.minute)
					+ ':' + os::datetime::ensure_two_digit_format(time_point.second)
			);
		}
	};

	struct hour_clock_24_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::hour_clock_24,
				os::datetime::ensure_two_digit_format(time_point.hour) 
					+ '-'  + os::datetime::ensure_two_digit_format(time_point.minute)
			);
		}
	};

	struct hour_clock_12_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::hour_clock_12,
				os::datetime::ensure_two_digit_format(time_point.hour)
					+ '-' + os::datetime::ensure_two_digit_format(time_point.minute)
					+ '-' + os::datetime::ensure_two_digit_format(time_point.second) 
					+ (time_point.hour >= 12 ? "pm" : "am")
			);
		}
	};

	struct ampm_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::ampm,
				time_point.hour >= 12 ? "pm" : "am"
			);
		}
	};

	struct hour_24_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::hour_24,
				os::datetime::ensure_two_digit_format(time_point.hour)
			);
		}
	};

	struct hour_12_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::hour_12,
				os::datetime::ensure_two_digit_format(os::datetime::to_12h(time_point.hour))
			);
		}
	};

	struct minute_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::minute,
				os::datetime::ensure_two_digit_format(time_point.minute)
			);
		}
	};

	struct second_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::second,
				os::datetime::ensure_two_digit_format(time_point.second)
			);
		}
	};

	struct millisecond_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::millisecond,
				os::datetime::ensure_two_digit_format(time_point.millisecond)
			);
		}
	};

	struct microsecond_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::microsecond,
				os::datetime::ensure_two_digit_format(time_point.microsecond)
			);
		}
	};

	struct nanosecond_formatter : public formatter
	{
		void format(memory_buffer<>& dst, const record_base& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter::format_attribute(
				dst,
				flag::nanosecond,
				os::datetime::ensure_two_digit_format(time_point.nanosecond)
			);
		}
	};
}