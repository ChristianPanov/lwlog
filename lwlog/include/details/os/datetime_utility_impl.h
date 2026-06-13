#pragma once

#include "datetime_utility.h"

namespace lwlog::details::os::datetime
{
	inline std::uint8_t to_12h(std::uint8_t hour)
	{
		return hour > 12 ? hour - 12 : hour;
	}

	inline timestamp_builder::timestamp_builder(char* buffer)
		: m_buffer{ buffer }
	{}

	template<std::uint8_t Width>
	timestamp_builder& timestamp_builder::append(std::size_t value)
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

	inline timestamp_builder& timestamp_builder::append_ampm(std::size_t hour)
	{
		m_buffer[m_pos] = (hour >= 12) ? 'p' : 'a';
		m_buffer[m_pos + 1] = 'm';

		m_pos += 2;

		return *this;
	}

	inline timestamp_builder& timestamp_builder::separate(char separator)
	{
		m_buffer[m_pos++] = separator;

		return *this;
	}

	inline const char* timestamp_builder::data() const
	{
		return m_buffer;
	}

	inline std::size_t timestamp_builder::size() const
	{
		return m_pos;
	}
}