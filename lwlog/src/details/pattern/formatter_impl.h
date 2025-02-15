#pragma once

namespace lwlog::details
{
	template<typename Config, typename BufferLimits>
	template<typename T>
	void formatter<Config, BufferLimits>::format_attribute(details::memory_buffer<BufferLimits::pattern>& pattern_buffer,
		char* conv_buffer, const flag_pair& flags, const T& value)
	{
		const auto& [verbose, shortened] = flags;

		convert_to_chars(conv_buffer, BufferLimits::conversion, value);

		std::size_t flag_pos{};
		while ((flag_pos = pattern_buffer.data().find(verbose.data())) != std::string_view::npos)
		{
			pattern_buffer.replace(flag_pos, verbose.length(), conv_buffer, std::strlen(conv_buffer));
		}

		while ((flag_pos = pattern_buffer.data().find(shortened.data())) != std::string_view::npos)
		{
			pattern_buffer.replace(flag_pos, shortened.length(), conv_buffer, std::strlen(conv_buffer));
		}
	}

	template<typename Config, typename BufferLimits>
	void formatter<Config, BufferLimits>::format_custom_attribute(details::memory_buffer<BufferLimits::pattern>& pattern_buffer,
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