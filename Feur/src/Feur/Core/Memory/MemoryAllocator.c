#include "fepch.h"
#include "Feur/Core/Memory/MemoryAllocator.h"

FE_INLINE_FUN void* FE_API FE_MemoryCustomMalloc(SizeT size)
{
	void* data = malloc(size);
	FE_CORE_ASSERT(data != NULL, "MemoryArena.c:: FE_CustomMalloc : failed to malloc");
	return data;
}

FE_INLINE_FUN UintptrT FE_API FE_MemoryAlignAddress(UintptrT address, SizeT alignment)
{
    return (address + (alignment - 1)) & ~(alignment - 1);
}

FE_INLINE_FUN UintptrT FE_API FE_MemoryAlignForwardAdjustment(UintptrT address, SizeT alignment)
{
    UintptrT adjustment = alignment - (address) & (alignment - 1);
    if (adjustment == alignment) return 0;

    return adjustment;
}

FE_INLINE_FUN UintptrT FE_API FE_MemoryAlignForwardAdjustmentWithHeader(UintptrT address, SizeT alignment, SizeT headerSize)
{
    UintptrT adjustment = FE_MemoryAlignAddress(address, alignment);
    UintptrT neededSpace = headerSize;

    if (adjustment < neededSpace)
    {
        neededSpace -= adjustment;

        //Increase adjustment to fit header 
        adjustment += alignment * (neededSpace / alignment);

        if (neededSpace % alignment > 0) adjustment += alignment;
    }

    return adjustment;
}





/*

=================== TESTS

*/
#include "ILDA_Matrix/ILDA_matrix.h"
#include "ILDA_vector/ILDA_vector.h"

void FE_API FE_MemoryStackAllocatorBenchmarkTest()
{
    //TEST MEMORY STACK
    FE_Benchmark AllocBenchmark;
    const Uint64 allocNum = 5;
    const Uint64 allocSize = 16;
    Uint64* results = FE_MemoryCustomMalloc(allocNum * sizeof(Uint64));

    FE_MemoryStackAllocator stackAlloc;
    FE_MemoryStackAllocatorInit(&stackAlloc, FE_MEMORY_DEFAULT_STACK_ALLOCATION_SIZE);

    for (Uint64 i = 0; i < allocNum; i++)
    {
        FE_BenchmarkStartClock(&AllocBenchmark);
        void* ptr = malloc(allocSize);
        FE_BenchmarkStopClock(&AllocBenchmark);
        results[i] = FE_BenchmarkClockNsDuration(&AllocBenchmark);
    }

    FE_MemoryStackAllocatorReset(&stackAlloc);

    //results malloc allocator
    Uint64 somme = 0;
    for (Uint64 i = 0; i < allocNum; i++)
    {
        somme += results[i];
    }
    Uint64 result = somme / allocNum;
    FE_BenchmarkShowDuration(result, "malloc allocations benchmark average duration");



    //TEST MEMORY STACK
    for (Uint64 i = 0; i < allocNum; i++)
    {
        FE_BenchmarkStartClock(&AllocBenchmark);
        void* ptr = FE_MemoryStackAllocatorAlloc(&stackAlloc, allocSize, FE_MEMORY_BASE_ALIGNEMENT);
        FE_BenchmarkStopClock(&AllocBenchmark);
        results[i] = FE_BenchmarkClockNsDuration(&AllocBenchmark);
    }

    //results stack allocator
    somme = 0;
    for (Uint64 i = 0; i < allocNum; i++)
    {
        somme += results[i];
    }
    result = somme / allocNum;
    FE_BenchmarkShowDuration(result, "stack allocations benchmark average duration");

    free(results);
}