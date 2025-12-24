#pragma once

#include "details/memory_buffer.h"
#include "details/record.h"

namespace lwlog::details::pattern_executor
{
    template<typename BufferLimits>
    struct pattern_context
    {
        memory_buffer<BufferLimits::pattern>& out;
        const record<BufferLimits>& record;

        const char* pattern_src{};

        char* conversion_buffer;
    };
}