#pragma once

#include <atomic>

#include "details/adaptive_waiter.h"

namespace lwlog
{
    struct spsc_model_policy {};
    struct mpsc_model_policy {};

    enum class overflow_action  : std::uint8_t { wait, overwrite_last, discard_new };
    enum class underflow_action : std::uint8_t { wait };

    struct block_overflow_policy {};
    struct overwrite_last_overflow_policy {};
    struct discard_new_overflow_policy {};

    template<typename Queue, typename OverflowPolicy>
    struct overflow_adapter
    {
        static overflow_action handle_full(Queue& queue)
        {
            if constexpr (std::is_same_v<OverflowPolicy, block_overflow_policy>)
            {
                LWLOG_CPU_PAUSE();
                return overflow_action::wait;
            }
            else if constexpr (std::is_same_v<OverflowPolicy, overwrite_last_overflow_policy>)
            {
                queue.advance_read_index();
                return overflow_action::overwrite_last;
            }
            else if constexpr (std::is_same_v<OverflowPolicy, discard_new_overflow_policy>)
            {
                return overflow_action::discard_new;
            }
        }

        static void handle_empty()
        {
            LWLOG_CPU_PAUSE();
        }
    };
}