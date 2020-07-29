#include "backtracer.h"

namespace lwlog::details
{
	void backtracer::backtrace(std::size_t chunk_size, std::size_t chunks)
	{
		m_is_enabled = true;
		m_buffer = { chunks, chunk_size };
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
		for (int i = 0; i < m_buffer.chunks(); ++i)
		{
			std::cout << m_buffer.output(i);
		}
	}

	void backtracer::dump()
	{
	}

	void backtracer::push_in_buffer(std::string_view message)
	{
		if (m_is_enabled == true)
		{
			m_buffer.store(m_stamp + message.data());
		}
	}

	bool backtracer::is_enabled() const
	{
		return m_is_enabled;
	}
}