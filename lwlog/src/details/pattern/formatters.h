#pragma once

#include "formatter.h"
#include "flag_data.h"
#include "level.h"

namespace lwlog::details
{
	template<typename Config, typename BufferLimits>
	struct level_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::level,
				level_details::to_string(record.log_level)
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct message_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::message,
				record.message
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct thread_id_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::thread_id,
				record.execution_context.thread_id()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct process_id_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::process_id,
				record.execution_context.process_id()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct line_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::line,
				record.meta.line()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct file_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::file,
				record.meta.file_name()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct function_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::function,
				record.meta.function_name()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct topic_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::topic,
				record.topic_registry.current_topic()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct full_topic_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::full_topic,
				record.topic_registry.full_topic()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct date_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::date, 
				os::datetime::timestamp_builder<10>()
				.append(time_point.year)
				.separate('-')
				.append(time_point.month)
				.separate('-')
				.append(time_point.day).data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct date_short_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::date_short, 
				os::datetime::timestamp_builder<8>()
				.append(time_point.month)
				.separate('/')
				.append(time_point.day)
				.separate('/')
				.append(time_point.year % 100).data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct year_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::year, 
				os::datetime::timestamp_builder<4>()
				.append(time_point.year)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct year_short_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::year_short, 
				os::datetime::timestamp_builder<2>()
				.append(time_point.year % 100)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct month_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::month, 
				os::datetime::timestamp_builder<2>()
				.append(time_point.month)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct month_name_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::month_name,
				os::datetime::month_name[time_point.month]
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct month_name_short_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::month_name_short,
				os::datetime::month_name_short[time_point.month]
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct day_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::day,
				os::datetime::timestamp_builder<2>()
				.append(time_point.day)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct weekday_name_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::weekday,
				os::datetime::weekday_name[time_point.weekday]
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct weekday_name_short_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::weekday_short,
				os::datetime::weekday_name_short[time_point.weekday]
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct time_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::time, 
				os::datetime::timestamp_builder<10>()
				.append(time_point.hour)
				.separate(':')
				.append(time_point.minute)
				.separate(':')
				.append(time_point.second)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct hour_clock_24_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::hour_clock_24, 
				os::datetime::timestamp_builder<5>()
				.append(time_point.hour)
				.separate(':')
				.append(time_point.minute)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct hour_clock_12_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::hour_clock_12, 
				os::datetime::timestamp_builder<10>()
				.append(time_point.hour)
				.separate(':')
				.append(time_point.minute)
				.separate(':')
				.append(time_point.second)
				.append_ampm(time_point.hour)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct ampm_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(
				pattern_buffer, conv_buffer,
				flag::ampm,
				time_point.hour >= 12 ? "pm" : "am"
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct hour_24_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::hour_24,
				os::datetime::timestamp_builder<2>()
				.append(time_point.hour)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct hour_12_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::hour_12,
				os::datetime::timestamp_builder<2>()
				.append(os::datetime::to_12h(time_point.hour))
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct minute_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::minute,
				os::datetime::timestamp_builder<2>()
				.append(time_point.minute)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct second_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::second,
				os::datetime::timestamp_builder<2>()
				.append(time_point.second)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct millisecond_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::millisecond,
				os::datetime::timestamp_builder<3>()
				.append(time_point.millisecond)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct microsecond_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::microsecond,
				os::datetime::timestamp_builder<6>()
				.append(time_point.microsecond)
				.data()
			);
		}
	};

	template<typename Config, typename BufferLimits>
	struct nanosecond_formatter : public formatter<Config, BufferLimits>
	{
		void format(details::memory_buffer<BufferLimits::pattern>& pattern_buffer, char* conv_buffer, 
			const record<Config, BufferLimits>& record) const override
		{
			const auto& time_point{ record.time_point };

			formatter<Config, BufferLimits>::format_attribute(pattern_buffer, conv_buffer, flag::nanosecond,
				os::datetime::timestamp_builder<9>()
				.append(time_point.nanosecond)
				.data()
			);
		}
	};
}