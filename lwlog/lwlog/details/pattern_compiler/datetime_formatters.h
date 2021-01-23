#pragma once

namespace lwlog::details
{
	struct date_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{date}", "%F",
				datetime::get_date(log_msg.time_point)
			);
		}
	};

	struct date_short_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{date_short}", "%D",
				datetime::get_date_short(log_msg.time_point)
			);
		}
	};

	struct year_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{year}", "%Y",
				datetime::get_year(log_msg.time_point)
			);
		}
	};

	struct year_short_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{year_short}", "%y",
				datetime::get_year_short(log_msg.time_point)
			);
		}
	};

	struct month_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{month}", "%m",
				datetime::get_month(log_msg.time_point)
			);
		}
	};

	struct month_name_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{month_name}", "%B",
				datetime::get_month_name(log_msg.time_point)
			);
		}
	};

	struct month_name_short_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{month_name_short}", "%b",
				datetime::get_month_name_short(log_msg.time_point)
			);
		}
	};

	struct day_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{day}", "%d",
				datetime::get_day(log_msg.time_point)
			);
		}
	};

	struct weekday_name_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{weekday}", "%A",
				datetime::get_weekday_name(log_msg.time_point)
			);
		}
	};

	struct weekday_name_short_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{weekday_short}", "%a",
				datetime::get_weekday_name_short(log_msg.time_point)
			);
		}
	};

	struct time_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{time}", "%T",
				datetime::get_time(log_msg.time_point)
			);
		}
	};

	struct hour_clock_24_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{24_clock}", "%R",
				datetime::get_24_hour_clock(log_msg.time_point)
			);
		}
	};

	struct hour_clock_12_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{12_clock}", "%r",
				datetime::get_12_hour_clock(log_msg.time_point)
			);
		}
	};

	struct ampm_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{ampm}", "%p",
				datetime::get_ampm(log_msg.time_point)
			);
		}
	};

	struct hour_24_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{hour_24}", "%H",
				datetime::get_hour_24(log_msg.time_point)
			);
		}
	};

	struct hour_12_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{hour_12}", "%I",
				datetime::get_hour_12(log_msg.time_point)
			);
		}
	};

	struct minute_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{minute}", "%M",
				datetime::get_minute(log_msg.time_point)
			);
		}
	};

	struct second_formatter : public formatter
	{
		virtual void format(log_message& log_msg) override
		{
			pattern_compiler::format_attribute(
				log_msg,
				"{second}", "%S",
				datetime::get_second(log_msg.time_point)
			);
		}
	};
}