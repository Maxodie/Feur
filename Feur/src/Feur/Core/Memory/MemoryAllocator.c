#include "fepch.h"
#include "Feur/Core/Memory/MemoryAllocator.h"

struct FE_MemoryGeneralAllocator
{
    FE_MemoryFreeListAllocator freeListAllocator;
} FE_MemoryGeneralAllocator;

FE_FORCEINLINE_FUN void* FE_API FE_MemoryCustomMalloc(SizeT size)
{
    void* data = malloc(size);
    FE_CORE_ASSERT(data != NULL, "failed to malloc");
    return data;
}

FE_FORCEINLINE_FUN void* FE_API FE_MemoryCustomCalloc(SizeT size)
{
    void* data = calloc(1, size);
    FE_CORE_ASSERT(data != NULL, "failed to calloc");
    return data;
}

FE_FORCEINLINE_FUN void FE_API FE_MemoryGeneralInit(SizeT size)
{
    void* mainFreeListMem = FE_MemoryCustomCalloc(size);
    FE_MemoryFreeListAllocatorInit(&FE_MemoryGeneralAllocator.freeListAllocator, size, mainFreeListMem);
}

FE_FORCEINLINE_FUN void* FE_API FE_MemoryGeneralAlloc(SizeT size)
{
    return FE_MemoryFreeListAllocatorAlloc(&FE_MemoryGeneralAllocator.freeListAllocator, size, FE_MEMORY_BASE_ALIGNEMENT);
}

FE_FORCEINLINE_FUN void FE_API FE_MemoryGeneralFree(void* ptr)
{
    FE_MemoryFreeListAllocatorFree(&FE_MemoryGeneralAllocator.freeListAllocator, ptr);
}

FE_FORCEINLINE_FUN void* FE_API FE_MemoryGeneralRealloc(void* ptr, SizeT size)
{
    return FE_MemoryFreeListAllocatorRealloc(&FE_MemoryGeneralAllocator.freeListAllocator, ptr, size, FE_MEMORY_BASE_ALIGNEMENT);
}

FE_FORCEINLINE_FUN UintptrT FE_API FE_MemoryAlignAddress(UintptrT address, SizeT alignment)
{
    return (address + (alignment - 1)) & ~(alignment - 1);
}

FE_FORCEINLINE_FUN UintptrT FE_API FE_MemoryAlignForwardAdjustment(UintptrT address, SizeT alignment)
{
    UintptrT adjustment = (UintptrT)(alignment - (address) & (alignment - 1));
    if (adjustment == alignment) return 0;

    return adjustment;
}

FE_FORCEINLINE_FUN UintptrT FE_API FE_MemoryAlignForwardAdjustmentWithHeader(UintptrT address, SizeT alignment, SizeT headerSize)
{
    UintptrT adjustment = FE_MemoryAlignForwardAdjustment(address, alignment);
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
    //TEST MEMORY malloc
    FE_Benchmark AllocBenchmark;
    const Uint64 allocNum = 5;
    const Uint64 allocSize = 16;
    Uint64* results = FE_MemoryCustomMalloc(allocNum * sizeof(Uint64));

    for (Uint64 i = 0; i < allocNum; i++)
    {
        FE_BenchmarkStartClock(&AllocBenchmark);
        void* ptr = malloc(allocSize);
        FE_BenchmarkStopClock(&AllocBenchmark);
        results[i] = FE_BenchmarkClockNsDuration(&AllocBenchmark);
    }

    //results malloc allocator
    FE_MemoryStackAllocator stackAllocator;
    void* memory = FE_MemoryCustomMalloc(FE_MEMORY_DEFAULT_STACK_ALLOCATION_SIZE);
    FE_MemoryStackAllocatorInit(&stackAllocator, FE_MEMORY_DEFAULT_STACK_ALLOCATION_SIZE, memory);

    Uint64 somme = 0;
    for (Uint64 i = 0; i < allocNum; i++)
    {
        somme += results[i];
    }
    Uint64 result = somme / allocNum;
    FE_BenchmarkShowDuration(result, "malloc allocations benchmark average duration");


    //TEST MEMORY Pool 
    for (Uint64 i = 0; i < allocNum; i++)
    {
        FE_BenchmarkStartClock(&AllocBenchmark);
        void* ptr = FE_MemoryStackAllocatorAlloc(&stackAllocator, allocSize, FE_MEMORY_BASE_ALIGNEMENT);
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
    free(memory);
}


void FE_API FE_MemoryPoolAllocatorBenchmarkTest()
{
    //TEST MEMORY malloc
    FE_Benchmark AllocBenchmark;
    const Uint64 allocNum = 5;
    const Uint64 allocSize = 16;
    Uint64* results = FE_MemoryCustomMalloc(allocNum * sizeof(Uint64));

    for (Uint64 i = 0; i < allocNum; i++)
    {
        FE_BenchmarkStartClock(&AllocBenchmark);
        void* ptr = malloc(allocSize);
        FE_BenchmarkStopClock(&AllocBenchmark);
        results[i] = FE_BenchmarkClockNsDuration(&AllocBenchmark);
    }

    //results malloc allocator
    Uint64 somme = 0;
    for (Uint64 i = 0; i < allocNum; i++)
    {
        somme += results[i];
    }
    Uint64 result = somme / allocNum;
    FE_BenchmarkShowDuration(result, "malloc allocations benchmark average duration");



    //TEST MEMORY Pool 
    SizeT defaultAllocSize = 2048;
    SizeT defaultAllocChunkSize = 128; //16 chunks (2048 / 128)
    FE_MemoryPoolAllocator poolAllocator; 
    void* memory = FE_MemoryCustomMalloc(defaultAllocSize);
    FE_MemoryPoolAllocatorInit(&poolAllocator, defaultAllocSize, defaultAllocChunkSize, FE_MEMORY_BASE_ALIGNEMENT, memory);

    for (Uint64 i = 0; i < allocNum; i++)
    {
        FE_BenchmarkStartClock(&AllocBenchmark);
        void* ptr = FE_MemoryPoolAllocatorAlloc(&poolAllocator, allocSize);
        FE_BenchmarkStopClock(&AllocBenchmark);
        results[i] = FE_BenchmarkClockNsDuration(&AllocBenchmark);
    }

    //results Pool allocator
    somme = 0;
    for (Uint64 i = 0; i < allocNum; i++)
    {
        somme += results[i];
    }
    result = somme / allocNum;
    FE_BenchmarkShowDuration(result, "Pool allocations benchmark average duration");

    free(results);
    //free(memory);
}

void FE_MemoryFreeListAllocatorBenchmarkTest()
{
    //TEST MEMORY malloc
    FE_Benchmark AllocBenchmark;
    const Uint64 allocNum = 5;
    const Uint64 allocSize = 16;
    Uint64* results = FE_MemoryCustomMalloc(allocNum * sizeof(Uint64));

    for (Uint64 i = 0; i < allocNum; i++)
    {
        FE_BenchmarkStartClock(&AllocBenchmark);
        void* ptr = malloc(allocSize);
        FE_BenchmarkStopClock(&AllocBenchmark);
        results[i] = FE_BenchmarkClockNsDuration(&AllocBenchmark);
    }

    //results malloc allocator
    Uint64 somme = 0;
    for (Uint64 i = 0; i < allocNum; i++)
    {
        somme += results[i];
    }
    Uint64 result = somme / allocNum;
    FE_BenchmarkShowDuration(result, "malloc allocations benchmark average duration");



    //TEST MEMORY Free list 
    SizeT defaultAllocSize = 2048;
    FE_MemoryFreeListAllocator freeListAllocator;
    void* memory = FE_MemoryCustomMalloc(defaultAllocSize);
    FE_MemoryFreeListAllocatorInit(&freeListAllocator, defaultAllocSize, memory);

    Uint64** test = FE_MemoryFreeListAllocatorAlloc(&freeListAllocator, sizeof(Uint64*) * allocNum, FE_MEMORY_BASE_ALIGNEMENT);

    for (Uint64 i = 0; i < allocNum; i++)
    {
        FE_BenchmarkStartClock(&AllocBenchmark);
        test[i] = FE_MemoryFreeListAllocatorAlloc(&freeListAllocator, allocSize, FE_MEMORY_BASE_ALIGNEMENT);
        FE_BenchmarkStopClock(&AllocBenchmark);
        results[i] = FE_BenchmarkClockNsDuration(&AllocBenchmark);

        *test[i] = i;
    }

    for (Uint64 i = allocNum - 1; i > 2; i--)
    {
        FE_MemoryFreeListAllocatorFree(&freeListAllocator, test[i]);
    }

    for (Uint64 i = 3; i < allocNum; i++)
    {
        test[i] = FE_MemoryFreeListAllocatorAlloc(&freeListAllocator, allocSize, FE_MEMORY_BASE_ALIGNEMENT);
        *test[i] = i*10;
    }

    for (Uint64 i = 0; i < allocNum; i++)
    {
        FE_CORE_LOG_DEBUG("value test : %lu", *test[i]);
    }

    //results Free list allocator
    somme = 0;
    for (Uint64 i = 0; i < allocNum; i++)
    {
        somme += results[i];
    }
    result = somme / allocNum;
    FE_BenchmarkShowDuration(result, "Free list allocations benchmark average duration");

    free(results);
    free(memory);
}
