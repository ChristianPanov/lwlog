#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "core.h"

namespace lwlog::details
{
	class LWLOG_API backtracer
	{
	public:
		void backtrace(std::size_t buffer_size);
		void disable();
		void set_stamp(std::string_view stamp);
		void display();
		void dump();
		void push_in_buffer(std::string_view message);
		bool is_enabled() const;

	private:
		bool m_is_enabled{ false };
		int m_messages{ 0 };
		std::string m_stamp;
		std::vector<std::string> m_buffer;
	};
}