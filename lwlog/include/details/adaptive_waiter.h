#pragma once

#include <cstdint>
#include <thread>

#if defined(__x86_64__) || defined(_M_X64)
    #include <immintrin.h>
    #define LWLOG_CPU_PAUSE() _mm_pause()
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define LWLOG_CPU_PAUSE() __asm__ volatile("yield")
#else
    #define LWLOG_CPU_PAUSE() std::this_thread::yield()
#endif

namespace lwlog::details
{
    template<std::uint16_t SpinLimit = 4000, std::uint16_t YieldLimit = 10000>
    class adaptive_waiter
    {
    public:
        void wait();
        void reset();

    private:
        std::uint16_t m_idle_cycles{};
    };

    template<std::uint16_t SpinLimit, std::uint16_t YieldLimit>
    void adaptive_waiter<SpinLimit, YieldLimit>::wait()
    {
        ++m_idle_cycles;

        if (m_idle_cycles < SpinLimit)
        {
            LWLOG_CPU_PAUSE();
        }
        else if (m_idle_cycles < YieldLimit)
        {
            std::this_thread::yield();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::microseconds(50));
        }
    }

    template<std::uint16_t SpinLimit, std::uint16_t YieldLimit>
    void adaptive_waiter<SpinLimit, YieldLimit>::reset()
    {
        m_idle_cycles = 0;
    }
}