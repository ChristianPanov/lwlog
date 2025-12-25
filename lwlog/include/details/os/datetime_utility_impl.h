#pragma once

#include "details/memory_buffer.h"
#include "datetime_utility.h"

namespace lwlog::details::os::datetime
{
	static std::uint8_t handle_timezone(std::uint8_t hour)
    {
		hour += cached_timezone_offset;
		hour = (hour <= 23) ? hour : hour - 24;

		return hour;
	}

	static std::uint8_t to_12h(std::uint8_t hour)
	{
		return hour > 12 ? hour - 12 : hour;
	}

	template<std::size_t Size>
	template<std::uint8_t Width>
	timestamp_builder<Size>& timestamp_builder<Size>::append(std::size_t value)
	{
		std::size_t remaining{ value };

		if constexpr (Width == 2) 
		{
			m_buffer[m_pos + 1] = char('0' + (remaining % 10)); remaining /= 10;
			m_buffer[m_pos + 0] = char('0' + (remaining % 10));

			m_pos += 2;
		}
		else if constexpr (Width == 3) 
		{
			m_buffer[m_pos + 2] = char('0' + (remaining % 10)); remaining /= 10;
			m_buffer[m_pos + 1] = char('0' + (remaining % 10)); remaining /= 10;
			m_buffer[m_pos + 0] = char('0' + (remaining % 10));

			m_pos += 3;
		}
		else
		{
			std::size_t write_pos{ m_pos + Width };

			for (std::uint8_t n = Width; n--;)
			{
				m_buffer[--write_pos] = char('0' + (remaining % 10));
				remaining /= 10;
			}

			m_pos += Width;
		}

		return *this;
	}

	template<std::size_t Size>
	timestamp_builder<Size>& timestamp_builder<Size>::append_ampm(std::size_t hour)
	{
		m_buffer[m_pos] = (hour >= 12) ? 'p' : 'a';
		m_buffer[m_pos + 1] = 'm';

		m_pos += 2;

		return *this;
	}

	template<std::size_t Size>
	timestamp_builder<Size>& timestamp_builder<Size>::separate(char separator)
	{
		m_buffer[m_pos++] = separator;

		return *this;
	}

	template<std::size_t Size>
	const char* timestamp_builder<Size>::data() const
	{
		return m_buffer;
	}
}