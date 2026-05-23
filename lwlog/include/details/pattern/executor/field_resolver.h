#pragma once

#include <string_view>

#include "details/pattern/pattern_instruction.h"
#include "details/record.h"
#include "level.h"

namespace lwlog::details::pattern_executor
{
	template<typename BufferLimits>
	std::string_view resolve_field(pattern_bytecode::builtin_field field, char* conv, const record<BufferLimits>& record)
	{
		switch (field)
		{
		case pattern_bytecode::builtin_field::level:
		{
			return level_details::to_string(record.log_level);
		}
		case pattern_bytecode::builtin_field::message:
		{
			return record.message;
		}
		case pattern_bytecode::builtin_field::thread_id:
		{
			const auto size{ convert_to_chars(conv, BufferLimits::conversion, 
				record.execution_context.thread_id) };
			return { conv, size };
		}
		case pattern_bytecode::builtin_field::process_id:
		{
			const auto size{ convert_to_chars(conv, BufferLimits::conversion, 
				record.execution_context.process_id) };
			return { conv, size };
		}
		case pattern_bytecode::builtin_field::line:
		{
			const auto size{ convert_to_chars(conv, BufferLimits::conversion,  
				record.meta.line()) };
			return { conv, size };
		}
		case pattern_bytecode::builtin_field::file:
		{
			return record.meta.file_name();
		}
		case pattern_bytecode::builtin_field::path:
		{
			return record.meta.file_path();
		}
		case pattern_bytecode::builtin_field::function:
		{
			return record.meta.function_name();
		}
		case pattern_bytecode::builtin_field::topic:
		{
			return record.topics.topics()[record.topic_index];
		}
		case pattern_bytecode::builtin_field::full_topic:
		{
			return record.topics.full_topic(record.topic_index);
		}
		case pattern_bytecode::builtin_field::date:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<10>(conv)
				.template append<4>(time_point.year)
				.separate('-')
				.template append<2>(time_point.month)
				.separate('-')
				.template append<2>(time_point.day)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::date_short:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<8>(conv)
				.template append<2>(time_point.month)
				.separate('/')
				.template append<2>(time_point.day)
				.separate('/')
				.template append<2>(time_point.year % 100)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::year:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<4>(conv)
				.template append<4>(time_point.year)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::year_short:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<2>(conv)
				.template append<2>(time_point.year % 100)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::month:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<2>(conv)
				.template append<2>(time_point.month)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::month_name:
		{
			return os::datetime::month_name[record.time_point.month - 1];
		}
		case pattern_bytecode::builtin_field::month_name_short:
		{
			return os::datetime::month_name_short[record.time_point.month - 1];
		}
		case pattern_bytecode::builtin_field::day:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<2>(conv)
				.template append<2>(time_point.day)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::weekday:
		{
			return os::datetime::weekday_name[record.time_point.weekday];
		}
		case pattern_bytecode::builtin_field::weekday_short:
		{
			return os::datetime::weekday_name_short[record.time_point.weekday];
		}
		case pattern_bytecode::builtin_field::time:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<8>(conv)
				.template append<2>(time_point.hour)
				.separate(':')
				.template append<2>(time_point.minute)
				.separate(':')
				.template append<2>(time_point.second)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::hour_clock_24:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<5>(conv)
				.template append<2>(time_point.hour)
				.separate(':')
				.template append<2>(time_point.minute)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::hour_clock_12:
		{
			const auto& time_point{ record.time_point };

			const auto hour_12{ os::datetime::to_12h(time_point.hour) };

			const auto timestamp{ os::datetime::timestamp_builder<10>(conv)
				.template append<2>(hour_12)
				.separate(':')
				.template append<2>(time_point.minute)
				.separate(':')
				.template append<2>(time_point.second)
				.append_ampm(time_point.hour)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::ampm:
		{
			const auto& time_point{ record.time_point };

			const char* const ampm{ (time_point.hour >= 12) ? "pm" : "am" };

			return { ampm, 2 };
		}
		case pattern_bytecode::builtin_field::hour_24:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<2>(conv)
				.template append<2>(time_point.hour)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::hour_12:
		{
			const auto& time_point{ record.time_point };

			const auto hour_12{ os::datetime::to_12h(time_point.hour) };

			const auto timestamp{ os::datetime::timestamp_builder<2>(conv)
				.template append<2>(hour_12)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::minute:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<2>(conv)
				.template append<2>(time_point.minute)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::second:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<2>(conv)
				.template append<2>(time_point.second)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::millisecond:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<3>(conv)
				.template append<3>(time_point.millisecond)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::microsecond:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<6>(conv)
				.template append<6>(time_point.microsecond)
			};

			return { timestamp.data(), timestamp.size() };
		}
		case pattern_bytecode::builtin_field::nanosecond:
		{
			const auto& time_point{ record.time_point };

			const auto timestamp{ os::datetime::timestamp_builder<9>(conv)
				.template append<9>(time_point.nanosecond)
			};

			return { timestamp.data(), timestamp.size() };
		}

		default:
			return { "", 0 };
		}
	}
}