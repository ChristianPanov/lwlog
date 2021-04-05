#pragma once

namespace lwlog::interface
{
	class logger
	{
	public:
		virtual ~logger() = default;

	public:
		virtual void sink_logs() = 0;

		virtual void set_pattern(std::string_view) = 0;
		virtual void set_level_filter(level) = 0;

		virtual void info(std::string_view) = 0;
		virtual void warning(std::string_view) = 0;
		virtual void error(std::string_view) = 0;
		virtual void critical(std::string_view) = 0;
		virtual void debug(std::string_view) = 0;

		virtual std::string_view name() const = 0;

	protected:
		virtual void log(std::string_view, level) = 0;
	};
}

namespace lwlog
{
	using logger_ptr = interface::logger*;
}