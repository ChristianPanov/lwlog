#pragma once

#include "file_sink.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	file_sink<ThreadingPolicy>::file_sink(std::string_view path, std::size_t size_limit)
		: m_size_limit{ size_limit }
		, m_file{ path }
	{
		m_file.open();
	}

	template<typename ThreadingPolicy>
	file_sink<ThreadingPolicy>::~file_sink()
	{
		m_file.close();
	}

	template<typename ThreadingPolicy>
	void file_sink<ThreadingPolicy>::sink_it(std::string_view message)
	{
		if (m_file.exists())
		{
			if (m_size_limit == 0 || m_file.size() <= m_size_limit)
			{
				m_file.reopen();
				m_file.write(message.data());
				m_file.close();
			}
		}
	}
}
