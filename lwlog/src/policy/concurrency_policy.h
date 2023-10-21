#pragma once

#include <atomic>
#include <xmmintrin.h>

namespace lwlog
{
    struct spsc_model_policy {};
    struct mpsc_model_policy {};

    struct block_overflow_policy 
    {
        static void handle_overflow()   { _mm_pause();  }
        static void handle_underflow()  { _mm_pause();  }
        static bool should_discard()    { return false; }
    };
    
    struct overwrite_last_overflow_policy
    {
        static void handle_overflow()   {}
        static void handle_underflow()  {}
        static bool should_discard()    { return false; }
    };

    struct discard_new_overflow_policy
    {
        static void handle_overflow()   { m_is_full.store(true, std::memory_order_relaxed);     }
        static void handle_underflow()  { m_is_full.store(false, std::memory_order_relaxed);    }
        static bool should_discard()    { return m_is_full.load(std::memory_order_relaxed);     }

    private:
        static inline std::atomic<bool> m_is_full{ false };
    };
}