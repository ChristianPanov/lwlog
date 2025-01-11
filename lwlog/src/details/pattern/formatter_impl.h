#pragma once

namespace lwlog::details
{
	template<typename T>
	void formatter::format_attribute(memory_buffer<>& buffer, const flag_pair& flags, T value)
	{
		const auto& [verbose, shortened] = flags;

		char conv_buffer[formatter::attribute_buffer_size]{};
		std::size_t value_size{ convert_to_chars(conv_buffer,
			formatter::attribute_buffer_size, value) };

		std::size_t flag_pos{};
		while ((flag_pos = buffer.data().find(verbose.data())) != std::string_view::npos)
		{
			buffer.replace(flag_pos, verbose.length(), conv_buffer, value_size);
		}

		while ((flag_pos = buffer.data().find(shortened.data())) != std::string_view::npos)
		{
			buffer.replace(flag_pos, shortened.length(), conv_buffer, value_size);
		}
	}

	inline void formatter::format_custom_attribute(memory_buffer<>& buffer, const attribute& attrib)
	{
		char conv_buffer[formatter::attribute_buffer_size]{};
		attrib.value_conv_callback(conv_buffer, formatter::attribute_buffer_size);

		std::size_t flag_pos{};
		while ((flag_pos = buffer.data().find(attrib.flag.data())) != std::string_view::npos)
		{
			buffer.replace(flag_pos, attrib.flag.length(), conv_buffer, std::strlen(conv_buffer));
		}
	}
}