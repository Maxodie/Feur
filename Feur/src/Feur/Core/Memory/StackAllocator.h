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

void FE_DECL FE_MemoryStackAllocatorInit(FE_MemoryStackAllocator* allocator, SizeT size, void* memory);

void* FE_DECL FE_MemoryStackAllocatorAlloc(FE_MemoryStackAllocator* allocator, SizeT size, SizeT alignment);
void FE_DECL FE_MemoryStackAllocatorFree(FE_MemoryStackAllocator* allocator);

// this function does not free anything
void FE_DECL FE_MemoryStackAllocatorClear(FE_MemoryStackAllocator* allocator);
void FE_DECL FE_MemoryStackAllocatorReset(FE_MemoryStackAllocator* allocator);