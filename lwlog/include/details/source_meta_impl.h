#include "source_meta.h"
#pragma once

namespace lwlog::details
{
	constexpr source_meta::source_meta(std::uint32_t line, const char* const file, const char* const function)
		: m_line{ line }
        , m_file{ file }
        , m_function{ function }
	{}

	constexpr source_meta source_meta::current(std::uint32_t line, const char* const file, const char* const function)
    {
		return { line, file, function };
    }

	constexpr std::uint32_t source_meta::line() const
	{
		return m_line;
	}

	constexpr const char* source_meta::file_path() const
    {
        return m_file;
    }

	constexpr const char* source_meta::file_name() const
	{
        const char* path_end{ m_file };

        while (*path_end != '\0')
        {
            ++path_end;
        }

        while (path_end != m_file)
        {
            --path_end;

            if (*path_end == '\\' || *path_end == '/')
            {
                return path_end + 1;
            }
        }

        return path_end;
	}

	constexpr const char* source_meta::function_name() const
	{
		return m_function;
	}
}