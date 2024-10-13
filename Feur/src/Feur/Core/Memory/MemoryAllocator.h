#pragma once
/*
=========== @TODO FE_MemoryAllocator struct and type enum in order to provide abstraction and easier allocations management (later mb)
*/
enum FE_MEMORY_ALLOCATION_INFO
{
	FE_MEMORY_DEFAULT_STACK_ALLOCATION_SIZE = 1024 * 200,

	FE_MEMORY_BASE_ALIGNEMENT = _Alignof (MaxAlignT),
	FE_MEMORY_DEFAULT_ALIGNEMENT = 0,

	FE_MEMORY_SMALL_POOL_ALLOCATION_SIZE = 1024 * 2,
	FE_MEMORY_MEDIUM_POOL_ALLOCATION_SIZE = 1024 * 10,
	FE_MEMORY_BIG_POOL_ALLOCATION_SIZE = 1024 * 100
};

void* FE_API FE_MemoryCustomMalloc(SizeT size);
UintptrT FE_API FE_MemoryAlignAddress(UintptrT address, SizeT alignment);
UintptrT FE_API FE_MemoryAlignForwardAdjustment(UintptrT address, SizeT alignment);
UintptrT FE_API FE_MemoryAlignForwardAdjustmentWithHeader(UintptrT address, SizeT alignment, SizeT headerSize);

#include "Feur/Core/Memory/StackAllocator.h"
#include "Feur/Core/Memory/PoolAllocator.h"


void FE_API FE_MemoryStackAllocatorBenchmarkTest();