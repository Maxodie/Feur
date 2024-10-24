#pragma once

typedef struct FE_FreeListFreeBlock 
{ 
	SizeT size; 
	struct FE_FreeListFreeBlock* next;
} FreeBlock;

typedef struct FE_MemoryFreeListAllocator
{
	FreeBlock* freeBlocks;
} FE_MemoryFreeListAllocator;

typedef struct FE_AllocationHeader
{ 
	SizeT size;
	UintptrT adjustment;
} FreeListAllocationHeader;

//@TODO use poolAllocator to make same sized pages to avoid fragmentation (mainly on small data (< 64byte))
void FE_API FE_MemoryFreeListAllocatorInit(FE_MemoryFreeListAllocator* allocator, SizeT size, const void* start);

void* FE_API FE_MemoryFreeListAllocatorAlloc(FE_MemoryFreeListAllocator* allocator, SizeT size, Uint8 alignment);
void FE_API FE_MemoryFreeListAllocatorFree(FE_MemoryFreeListAllocator* allocator, void* ptr);
void* FE_API FE_MemoryFreeListAllocatorRealloc(FE_MemoryFreeListAllocator* allocator, void* ptr, SizeT size, Uint8 alignment);