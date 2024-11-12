#pragma once

typedef struct FE_MemoryPoolAllocator
{
	void** freeData;
	//Int8 chunkAdjustment;
	SizeT chunkSize;
} FE_MemoryPoolAllocator;

void FE_DECL FE_MemoryPoolAllocatorInit(FE_MemoryPoolAllocator* allocator, SizeT blockSize, SizeT chunkSize, SizeT alignment, const void* memory);

void* FE_DECL FE_MemoryPoolAllocatorAlloc(FE_MemoryPoolAllocator* allocator, SizeT size);
void FE_DECL FE_MemoryPoolAllocatorFree(FE_MemoryPoolAllocator* allocator, void* ptr);