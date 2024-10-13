#pragma once

#if defined(__linux)
#  define HAVE_POSIX_TIMER
#  include <time.h>
#  ifdef CLOCK_MONOTONIC
#     define CLOCKID CLOCK_MONOTONIC
#  else
#     define CLOCKID CLOCK_REALTIME
#  endif
#elif defined(__APPLE__)
#  define HAVE_MACH_TIMER
#  include <mach/mach_time.h>
#elif defined(_WIN32)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

/*

 ================= Multithreading not supported =================

*/


typedef struct FE_Benchmark
{
	Uint64 startTime;
	Uint64 endTime;
} FE_Benchmark;

void FE_API FE_BenchmarkStartClock(FE_Benchmark* benchmark);
void FE_API FE_BenchmarkStopClock(FE_Benchmark* benchmark);
Uint64 FE_API FE_BenchmarkClockNsDuration(FE_Benchmark* benchmark);

void FE_API FE_BenchmarkShowDuration(Uint64 nanoSeconds, const char* prefix);