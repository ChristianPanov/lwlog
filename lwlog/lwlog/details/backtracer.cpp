#include "backtracer.h"

namespace lwlog::details
{
	void backtracer::backtrace(std::size_t buffer_size)
	{
		m_is_enabled = true;
		m_buffer.reserve(buffer_size);
	}

	void backtracer::disable()
	{
		m_is_enabled = false;
	}

	void backtracer::set_stamp(std::string_view stamp)
	{
		m_stamp = stamp;
	}
 
	void backtracer::display()
	{
		for (const auto& message : m_buffer)
		{
			std::cout << m_stamp + message << '\n';
		}
	}

	void backtracer::dump()
	{
		m_messages = 0;
		m_buffer.clear();
	}

	void backtracer::push_in_buffer(std::string_view message)
	{
		if (m_is_enabled == true)
		{
			m_messages++;
			if (m_messages <= m_buffer.capacity())
			{
				m_buffer.emplace_back(message);
			}
		}
	}

	bool backtracer::is_enabled() const
	{
		return m_is_enabled;
	}
}