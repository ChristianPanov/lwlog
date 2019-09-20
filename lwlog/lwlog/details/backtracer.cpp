#include "backtracer.h"

#include "../print.h"

namespace details
{
	backtracer::backtracer()
		: m_backtrace_messages(0)
		, m_is_backtrace_enabled(false)
	{
	}

	void backtracer::backtrace(std::size_t buffer_size)
	{
		m_is_backtrace_enabled = true;
		m_backtrace_buffer.reserve(buffer_size);
	}

	void backtracer::set_backtrace_stamp(std::string_view stamp)
	{
		m_backtrace_stamp = stamp;
	}
 
	void backtracer::display_backtrace()
	{
		for (const auto& i : m_backtrace_buffer)
		{
			lwlog::print("{0}{1}\n", m_backtrace_stamp, i);
		}
	}

	void backtracer::delete_backtrace()
	{
		m_backtrace_messages = 0;
		m_backtrace_buffer.clear();
	}

	void backtracer::push_in_backtrace_buffer(std::string_view message)
	{
		if (m_is_backtrace_enabled == true)
		{
			m_backtrace_messages++;
			if (m_backtrace_messages <= m_backtrace_buffer.capacity())
			{
				m_backtrace_buffer.emplace_back(message);
			}
		}
	}
}