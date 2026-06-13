#pragma once

#include "details/memory_buffer.h"
#include "details/record.h"
#include "details/pattern/custom_field.h"

namespace lwlog::details::pattern_executor
{
    template<typename BufferLimits>
    struct pattern_context
    {
        memory_buffer<BufferLimits::pattern>& out;
        const record& log_record;

        const char* pattern_src{};

        char* conversion_buffer;

        const details::custom_field* custom_fields{};
    };
}