#pragma once

#include <atomic>
#include <xmmintrin.h>

namespace lwlog
{
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
        static void handle_overflow()   { m_is_full.store(true); }
        static void handle_underflow()  { m_is_full.store(false); }
        static bool should_discard()    { return m_is_full.load(); }

    private:
        static inline std::atomic<bool> m_is_full{ false };
    };
}