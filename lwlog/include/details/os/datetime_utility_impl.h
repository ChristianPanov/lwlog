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
	timestamp_builder<Size>& timestamp_builder<Size>::append(std::size_t value)
	{
		if (value <= 9)
		{
			m_buffer[m_pos++] = '0';
		}

		const auto [ptr, ec]{ std::to_chars(m_buffer + m_pos, m_buffer + Size, value) };
		m_pos = ptr - m_buffer;

		return *this;
	}

	template<std::size_t Size>
	timestamp_builder<Size>& timestamp_builder<Size>::append_ampm(std::size_t hour)
	{
		std::memcpy(m_buffer + m_pos, hour >= 12 ? "pm" : "am", 2);
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