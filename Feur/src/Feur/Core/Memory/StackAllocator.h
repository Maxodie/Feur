#pragma once

typedef struct FE_MemoryStackAllocatorHeader
{
	void* blockStart;
} FE_MemoryStackAllocatorHeader;

typedef struct FE_MemoryStackAllocator
{
	void* data;
	UintptrT top; // default = data
	SizeT size;
} FE_MemoryStackAllocator;

void FE_API FE_MemoryStackAllocatorInit(FE_MemoryStackAllocator* allocator, SizeT size);

void* FE_API FE_MemoryStackAllocatorAlloc(FE_MemoryStackAllocator* allocator, SizeT size, SizeT alignment);
void FE_API FE_MemoryStackAllocatorFree(FE_MemoryStackAllocator* allocator);

void FE_API FE_MemoryStackAllocatorClear(FE_MemoryStackAllocator* allocator);
void FE_API FE_MemoryStackAllocatorReset(FE_MemoryStackAllocator* allocator);

void FE_API FE_MemoryStackAllocatorPrint(FE_MemoryStackAllocator* allocator);