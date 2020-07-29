#include "conjugate_memory_buffer.h"

namespace lwlog::details
{
	chunk_t::chunk_t(std::size_t size)
		: m_size{ size }
	{}

	void chunk_t::store(std::string_view data)
	{
		if (m_elements++ + 1 <= m_size)
		{
			m_chunk_buffer += data.data();
			m_chunk_buffer += '\n';
		}
	}

	bool chunk_t::is_full() const
	{
		return m_elements == m_size;
	}

	std::string& chunk_t::data()
	{
		return m_chunk_buffer;
	}

	conjugate_memory_buffer::conjugate_memory_buffer(std::size_t chunk_size, std::size_t chunks)
		: m_chunks{ chunks }
	{
		m_chunk_buffer.reserve(m_chunks);
		for (std::size_t i = 0; i < m_chunks; ++i)
		{
			m_chunk_buffer.push_back({ chunk_size });
		}
	}

	void conjugate_memory_buffer::store(std::string_view data)
	{
		if (m_pos < m_chunk_buffer.size())
		{
			if (!m_chunk_buffer[m_pos].is_full())
			{
				m_chunk_buffer[m_pos].store(data);
			}
			else if (m_pos != m_chunk_buffer.size() - 1)
			{
				m_chunk_buffer[++m_pos].store(data);
			}
		}
	}

	std::string conjugate_memory_buffer::output(std::size_t pos)
	{
		return m_chunk_buffer[pos].data();
	}

	std::size_t conjugate_memory_buffer::chunks() const
	{
		return m_chunks;
	}
}