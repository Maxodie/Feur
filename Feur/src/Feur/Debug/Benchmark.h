#pragma once

/*

 ================= Multithreading not supported =================

*/


typedef struct FE_Benchmark
{
	Uint64 startTime;
	Uint64 endTime;
} FE_Benchmark;

#define FE_NS_TIME_PER_SEC 1000000000
#define FE_NS_TIME_PER_MS 1000000
Uint64 FE_DECL FE_GetCurrentTimeNs();

void FE_DECL FE_BenchmarkStartClock(FE_Benchmark* benchmark);
void FE_DECL FE_BenchmarkStopClock(FE_Benchmark* benchmark);
Uint64 FE_DECL FE_BenchmarkClockNsDuration(FE_Benchmark* benchmark);

void FE_DECL FE_BenchmarkShowDuration(Uint64 nanoSeconds, const char* prefix);