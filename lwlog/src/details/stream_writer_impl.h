#pragma once

#include "stream_writer.h"

#include <cstdio>

namespace lwlog::details
{
    template<typename FlushPolicy>
    stream_writer<FlushPolicy>::stream_writer(std::FILE* stream)
        : m_stream{ stream }
    {
        std::setvbuf(m_stream, nullptr, _IOFBF, FlushPolicy::buffer_size);
    }

    template<typename FlushPolicy>
    stream_writer<FlushPolicy>::stream_writer(std::string_view path)
        : m_path{ path }
    {
        if (!std::filesystem::exists(m_path.parent_path()))
        {
            std::filesystem::create_directory(m_path.parent_path());
        }

#if defined(WIN32)
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif #defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
#endif
        m_stream = std::fopen(m_path.string().data(), "a");
#if defined(WIN32)
#if defined(_MSC_VER)
#pragma warning(pop)
#elif #defined(__clang__)
#pragma clang diagnostic pop
#endif
#endif

        if (m_stream != nullptr)
        {
            std::setvbuf(m_stream, nullptr, _IOFBF, FlushPolicy::buffer_size);
        }
    }

    template<typename FlushPolicy>
    stream_writer<FlushPolicy>::~stream_writer()
    {
        if (!m_path.empty() && m_stream != nullptr)
        {
            std::fclose(m_stream);
            m_stream = nullptr;
        }
    }

    template<typename FlushPolicy>
    void stream_writer<FlushPolicy>::write(std::string_view message) const
    {
        if (m_stream != nullptr)
        {
            std::fwrite(message.data(), message.size(), 1, m_stream);
            std::fwrite("\n", 1, 1, m_stream);
            FlushPolicy::flush(m_stream);
        }
    }

    template<typename FlushPolicy>
    std::FILE* stream_writer<FlushPolicy>::handle() const
    {
        return m_stream;
    }

    template<typename FlushPolicy>
    std::filesystem::path& stream_writer<FlushPolicy>::filesystem_path()
    {
        return m_path;
    }
}
