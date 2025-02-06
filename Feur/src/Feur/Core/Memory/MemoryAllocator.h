#pragma once
/*
=========== @TODO FE_MemoryAllocator struct and type enum in order to provide abstraction and easier allocations management (later mb)
*/
enum FE_MEMORY_ALLOCATION_INFO
{
	FE_MEMORY_DEFAULT_STACK_ALLOCATION_SIZE = 2024 * 10000,

	FE_MEMORY_BASE_ALIGNEMENT = FE_ALIGN_OF(MaxAlignT),
	FE_MEMORY_DEFAULT_ALIGNEMENT = 0,


	FE_MEMORY_SMALL_POOL_ALLOCATION_SIZE = 1024 * 20,
	FE_MEMORY_SMALL_POOL_ALLOCATION_CHUNK_SIZE = FE_MEMORY_SMALL_POOL_ALLOCATION_SIZE / 16,

	FE_MEMORY_MEDIUM_POOL_ALLOCATION_SIZE = 1024 * 10,
	FE_MEMORY_MEDIUM_POOL_ALLOCATION_CHUNK_SIZE = FE_MEMORY_MEDIUM_POOL_ALLOCATION_SIZE / 4,

	FE_MEMORY_BIG_POOL_ALLOCATION_SIZE = 1024 * 100,
	FE_MEMORY_BIG_POOL_ALLOCATION_CHUNK_SIZE = FE_MEMORY_BIG_POOL_ALLOCATION_SIZE / 4
};

//@TODO general allocation that allocate pool page, maybe with a system of a different sized 

//FE_FORCEINLINE_FUN void* FE_DECL FE_MemoryCustomMalloc(SizeT size);
//FE_FORCEINLINE_FUN void* FE_DECL FE_MemoryCustomCalloc(SizeT size);
FE_FORCEINLINE_FUN UintptrT FE_DECL FE_MemoryAlignAddress(UintptrT address, SizeT alignment);
FE_FORCEINLINE_FUN UintptrT FE_DECL FE_MemoryAlignForwardAdjustment(UintptrT address, SizeT alignment);
FE_FORCEINLINE_FUN UintptrT FE_DECL FE_MemoryAlignForwardAdjustmentWithHeader(UintptrT address, SizeT alignment, SizeT headerSize);

FE_FORCEINLINE_FUN void FE_DECL FE_MemoryGeneralInit(SizeT size);
FE_FORCEINLINE_FUN void FE_DECL FE_MemoryGeneralShutdown();
//@TODO maybe made a gameloop allocation using stack alloc (or linear) and free it every frame
FE_FORCEINLINE_FUN void* FE_DECL FE_MemoryGeneralAlloc(SizeT size);
FE_FORCEINLINE_FUN void FE_DECL FE_MemoryGeneralFree(void* ptr);
FE_FORCEINLINE_FUN void* FE_DECL FE_MemoryGeneralRealloc(void* ptr, SizeT size);

void FE_DECL FE_MemoryStackAllocatorBenchmarkTest();
void FE_DECL FE_MemoryPoolAllocatorBenchmarkTest(); 
void FE_DECL FE_MemoryFreeListAllocatorBenchmarkTest();