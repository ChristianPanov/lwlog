#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "conjugate_memory_buffer.h"

namespace lwlog::details
{
	class backtracer
	{
	public:
		void backtrace(std::size_t chunk_size, std::size_t chunks);
		void disable();
		void set_stamp(std::string_view stamp);
		void display();
		void dump();
		void push_in_buffer(std::string_view message);
		bool is_enabled() const;

	private:
		bool m_is_enabled{ false };
		std::string m_stamp{ "[BACKTRACE]" };
		conjugate_memory_buffer m_buffer;
	};
}