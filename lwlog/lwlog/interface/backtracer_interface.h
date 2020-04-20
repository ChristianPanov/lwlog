#pragma once

namespace lwlog::interface
{
	class backtracer
	{
	public:
		virtual ~backtracer() = default;
		virtual void backtrace(std::size_t) = 0;
		virtual void disable_backtrace() = 0;
		virtual void set_backtrace_stamp(std::string_view) = 0;
		virtual void display_backtrace() = 0;
		virtual void dump_backtrace() = 0;
		virtual bool is_backtrace_enabled() const = 0;
	};
}