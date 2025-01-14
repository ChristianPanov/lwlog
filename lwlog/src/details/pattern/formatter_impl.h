#pragma once

namespace lwlog::details
{
	template<typename Config, typename BufferLimits>
	template<typename T>
	void formatter<Config, BufferLimits>::format_attribute(memory_buffer<BufferLimits::pattern>& buffer,
		const flag_pair& flags, T value)
	{
		const auto& [verbose, shortened] = flags;

		char conv_buffer[BufferLimits::conversion]{};
		convert_to_chars(conv_buffer, BufferLimits::conversion, value);

		std::size_t flag_pos{};
		while ((flag_pos = buffer.data().find(verbose.data())) != std::string_view::npos)
		{
			buffer.replace(flag_pos, verbose.length(), conv_buffer, std::strlen(conv_buffer));
		}

		while ((flag_pos = buffer.data().find(shortened.data())) != std::string_view::npos)
		{
			buffer.replace(flag_pos, shortened.length(), conv_buffer, std::strlen(conv_buffer));
		}
	}

	template<typename Config, typename BufferLimits>
	void formatter<Config, BufferLimits>::format_custom_attribute(memory_buffer<BufferLimits::pattern>& buffer, 
		const attribute& attrib)
	{
		char conv_buffer[BufferLimits::conversion]{};
		attrib.value_conv_callback(conv_buffer, BufferLimits::conversion);

		std::size_t flag_pos{};
		while ((flag_pos = buffer.data().find(attrib.flag.data())) != std::string_view::npos)
		{
			buffer.replace(flag_pos, attrib.flag.length(), conv_buffer, std::strlen(conv_buffer));
		}
	}
}