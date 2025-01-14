#pragma once

#include "formatter.h"
#include "flag_data.h"
#include "level.h"

namespace lwlog::details
{
	template<typename Config, typename BufferLimits>
	struct level_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::level,
				level_details::to_string(record.log_level)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct message_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::message,
				record.message_buffer.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct thread_id_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::thread_id,
				record.exec_context().thread_id()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct process_id_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::process_id,
				record.exec_context().process_id()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct line_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::line,
				record.meta.line()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct file_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::file,
				record.meta.file_name()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct function_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::function,
				record.meta.function_name()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct topic_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::topic,
				record.get_topic_registry().current_topic()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct full_topic_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::full_topic,
				record.get_topic_registry().full_topic()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct date_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::date,
				os::datetime::ensure_two_digit_format(time_point.year)
					+ '-' + os::datetime::ensure_two_digit_format(time_point.month)
					+ '-' + os::datetime::ensure_two_digit_format(time_point.day)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct date_short_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::date_short,
				os::datetime::ensure_two_digit_format(time_point.month) 
					+ '/' + os::datetime::ensure_two_digit_format(time_point.day) 
					+ '/'+ os::datetime::ensure_two_digit_format(time_point.year % 100)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct year_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::year,
				os::datetime::ensure_two_digit_format(time_point.year)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct year_short_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::year_short,
				os::datetime::ensure_two_digit_format(time_point.year % 100)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct month_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::month,
				os::datetime::ensure_two_digit_format(time_point.month)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct month_name_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::month_name,
				os::datetime::month_name[time_point.month]
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct month_name_short_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::month_name_short,
				os::datetime::month_name_short[time_point.month]
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct day_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::day,
				os::datetime::ensure_two_digit_format(time_point.day)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct weekday_name_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::weekday,
				os::datetime::weekday_name[time_point.weekday]
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct weekday_name_short_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::weekday_short,
				os::datetime::weekday_name_short[time_point.weekday]
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct time_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::time,
				os::datetime::ensure_two_digit_format(time_point.hour)
					+ ':' + os::datetime::ensure_two_digit_format(time_point.minute)
					+ ':' + os::datetime::ensure_two_digit_format(time_point.second)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct hour_clock_24_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::hour_clock_24,
				os::datetime::ensure_two_digit_format(time_point.hour) 
					+ '-'  + os::datetime::ensure_two_digit_format(time_point.minute)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct hour_clock_12_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::hour_clock_12,
				os::datetime::ensure_two_digit_format(time_point.hour)
					+ '-' + os::datetime::ensure_two_digit_format(time_point.minute)
					+ '-' + os::datetime::ensure_two_digit_format(time_point.second) 
					+ (time_point.hour >= 12 ? "pm" : "am")
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct ampm_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::ampm,
				time_point.hour >= 12 ? "pm" : "am"
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct hour_24_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::hour_24,
				os::datetime::ensure_two_digit_format(time_point.hour)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct hour_12_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::hour_12,
				os::datetime::ensure_two_digit_format(os::datetime::to_12h(time_point.hour))
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct minute_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::minute,
				os::datetime::ensure_two_digit_format(time_point.minute)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct second_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::second,
				os::datetime::ensure_two_digit_format(time_point.second)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct millisecond_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::millisecond,
				os::datetime::ensure_two_digit_format(time_point.millisecond)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct microsecond_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::microsecond,
				os::datetime::ensure_two_digit_format(time_point.microsecond)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct nanosecond_formatter : public formatter<Config, BufferLimits>
	{
		void format(memory_buffer<BufferLimits::pattern>& dst, const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point() };

			formatter<Config, BufferLimits>::format_attribute(
				dst,
				flag::nanosecond,
				os::datetime::ensure_two_digit_format(time_point.nanosecond)
			);
		}
	};
}