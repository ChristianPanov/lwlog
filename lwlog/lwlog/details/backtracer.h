#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "../core.h"

namespace details
{
	class LWLOG_API backtracer
	{
	public:
		backtracer();
		virtual ~backtracer() = default;

		void backtrace(std::size_t buffer_size);
		void disable_backtrace();
		void set_backtrace_stamp(std::string_view stamp);
		void display_backtrace();
		void delete_backtrace();
		void push_in_backtrace_buffer(std::string_view message);

	private:
		std::vector<std::string> m_backtrace_buffer;
		std::string m_backtrace_stamp;
		int m_backtrace_messages;
		bool m_is_backtrace_enabled;
	};
}