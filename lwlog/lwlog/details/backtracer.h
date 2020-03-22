#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "core.h"

namespace lwlog::details
{
	class LWLOG_API backtracer
	{
	public:
		void backtrace(std::size_t buffer_size);
		void disable_backtrace();
		void set_backtrace_stamp(std::string_view stamp);
		void display_backtrace();
		void delete_backtrace();
		void push_in_backtrace_buffer(std::string_view message);

	private:
		bool m_is_backtrace_enabled{ false };
		int m_backtrace_messages{ 0 };
		std::string m_backtrace_stamp;
		std::vector<std::string> m_backtrace_buffer;
	};
}