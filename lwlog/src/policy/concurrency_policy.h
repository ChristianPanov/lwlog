#pragma once

#include <atomic>

#if defined(__x86_64__) || defined(_M_X64)
    #include <xmmintrin.h>
    #define CPU_PAUSE() _mm_pause
#elif defined(__aarch64_)
    #include <arm_acle.h>
    #define CPU_PAUSE() __yield
#else
    #define CPU_PAUSE()
#endif

namespace lwlog
{
    struct spsc_model_policy {};
    struct mpsc_model_policy {};

    struct block_overflow_policy 
    {
        static void handle_overflow()   { CPU_PAUSE();  }
        static void handle_underflow()  { CPU_PAUSE();  }
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
        static inline std::atomic_bool m_is_full{ false };
    };
}