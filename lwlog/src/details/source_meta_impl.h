#pragma once

namespace lwlog::details
{
    constexpr source_meta source_meta::current(std::uint32_t line, std::string_view file, std::string_view function)
    {
		source_meta meta;

		meta.m_line = line;
		meta.m_file = file;
		meta.m_function = function;

		return meta;
    }

	constexpr std::uint32_t source_meta::line() const
	{
		return m_line;
	}

	constexpr std::string_view source_meta::file_name() const
	{
		return m_file;
	}

	constexpr std::string_view source_meta::function_name() const
	{
		return m_function;
	}
}