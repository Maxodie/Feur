#include "fepch.h"
#include "Feur/Debug/Benchmark.h"



void FE_DECL FE_BenchmarkStartClock(FE_Benchmark* benchmark)
{
    benchmark->startTime = FE_GetCurrentTimeNs();
}

void FE_DECL FE_BenchmarkStopClock(FE_Benchmark* benchmark)
{
	benchmark->endTime = FE_GetCurrentTimeNs();
}

Uint64 FE_DECL FE_BenchmarkClockNsDuration(FE_Benchmark* benchmark)
{
    FE_CORE_ASSERT(benchmark->startTime <= benchmark->endTime, "The benchmark clock has not been stopped");
	return benchmark->endTime - benchmark->startTime;
}

void FE_DECL FE_BenchmarkShowDuration(Uint64 nanoSeconds, const char* prefix)
{
    Uint64 ns = nanoSeconds % 1000;
    nanoSeconds /= 1000;
    Uint64 macroSeconds = nanoSeconds % 1000;
    nanoSeconds /= 1000;
    Uint64 miliSeconds = nanoSeconds % 1000;
    nanoSeconds /= 1000;
    Uint64 seconds = nanoSeconds % 1000;
    FE_CORE_LOG_DEBUG("%s [%lu:%03lu:%03lu:%03lu]", prefix, seconds, miliSeconds, macroSeconds, ns);
}

Uint64 FE_DECL FE_GetCurrentTimeNs() 
{
    static Bool is_init = FALSE;
#if defined(__APPLE__) || defined(FE_PLATFORM_MACOS)
    static mach_timebase_info_data_t info;
    if (FALSE == is_init) {
        mach_timebase_info(&info);
        is_init = TRUE;
    }
    Uint64 now;
    now = mach_absolute_time();
    now *= info.numer;
    now /= info.denom;
    return now;
#elif defined(__linux) || defined(FE_PLATFORM_LINUX)
    static struct timespec linux_rate;
    if (FALSE == is_init) {
        clock_getres(CLOCKID, &linux_rate);
        is_init = TRUE;
    }
    Uint64 now;
    struct timespec spec;
    clock_gettime(CLOCKID, &spec);
    now = spec.tv_sec * 1.0e9 + spec.tv_nsec;
    return now;
#elif defined(_WIN32) || defined(FE_PLATFORM_WINDOWS)
    static LARGE_INTEGER win_frequency;
    if (FALSE == is_init) {
        QueryPerformanceFrequency(&win_frequency);
        is_init = TRUE;
    }
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (Uint64)((1e9 * now.QuadPart) / win_frequency.QuadPart);
#endif
}