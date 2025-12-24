#include "source_meta.h"
#pragma once

namespace lwlog::details
{
	constexpr source_meta::source_meta(std::uint32_t line, std::string_view file, std::string_view function)
		: m_line{ line }
        , m_file{ file }
        , m_function{ function }
	{}

	constexpr source_meta source_meta::current(std::uint32_t line, std::string_view file, std::string_view function)
    {
		return { line, file, function };
    }

	constexpr std::uint32_t source_meta::line() const
	{
		return m_line;
	}

	constexpr std::string_view source_meta::file_path() const
    {
        return m_file;
    }

	constexpr std::string_view source_meta::file_name() const
	{
        if (m_file.empty())
        {
            return {};
        }

        for (std::size_t i = m_file.size(); i > 0; --i)
        {
            const char c{ m_file[i - 1] };
            if (c == '/' || c == '\\')
            {
                return m_file.substr(i);
            }
        }

        return m_file;
	}

	constexpr std::string_view source_meta::function_name() const
	{
		return m_function;
	}

    constexpr bool source_meta::is_initialized() const
    {
        return m_line != 0 && !m_file.empty() && !m_function.empty();
    }
}