#pragma once

namespace lwlog::details
{
	template<typename BufferLimits>
	template<typename T>
	void formatter<BufferLimits>::format_attribute(details::memory_buffer<BufferLimits::pattern>& pattern_buffer,
		char* conv_buffer, const flag_pair& flags, const T& value)
	{
		const auto& [verbose, shortened] = flags;

		const char* final_value; 
		std::size_t value_length;

        if constexpr (std::is_same_v<T, const char*>)
        {
            final_value = value;
			value_length = std::strlen(value);
        }
        else
        {
			convert_to_chars(conv_buffer, BufferLimits::conversion, value);

            final_value = conv_buffer;
			value_length = std::strlen(conv_buffer);
        }

		std::size_t flag_pos{};
		while ((flag_pos = pattern_buffer.data().find(verbose.data())) != std::string_view::npos)
		{
			pattern_buffer.replace(flag_pos, verbose.length(), final_value, value_length);
		}

		while ((flag_pos = pattern_buffer.data().find(shortened.data())) != std::string_view::npos)
		{
			pattern_buffer.replace(flag_pos, shortened.length(), final_value, value_length);
		}
	}

	template<typename BufferLimits>
	void formatter<BufferLimits>::format_custom_attribute(details::memory_buffer<BufferLimits::pattern>& pattern_buffer,
		char* conv_buffer, const attribute& attrib)
	{
		attrib.value_conv_callback(conv_buffer, BufferLimits::conversion);

		std::size_t flag_pos{};
		while ((flag_pos = pattern_buffer.data().find(attrib.flag.data())) != std::string_view::npos)
		{
			pattern_buffer.replace(flag_pos, attrib.flag.length(), conv_buffer, std::strlen(conv_buffer));
		}
	}
}