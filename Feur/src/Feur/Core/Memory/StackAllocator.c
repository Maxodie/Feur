#include "fepch.h"
#include "Feur/Core/Memory/StackAllocator.h"

void FE_API FE_MemoryStackAllocatorInit(FE_MemoryStackAllocator* allocator, SizeT size, const void* memory)
{
	allocator->data = memory;
	allocator->top = (UintptrT)allocator->data;
	allocator->size = size;
}

void* FE_API FE_MemoryStackAllocatorAlloc(FE_MemoryStackAllocator* allocator, SizeT size, SizeT alignment)
{
	//Int8 adjustment = FE_MemoryAlignForwardAdjustment(allocator->top, alignment);
	//UintptrT alignedAddress = adjustment + allocator->top;
	UintptrT alignedAddress = FE_MemoryAlignForwardAdjustment(allocator->top, alignment) + allocator->top;

	//FE_CORE_ASSERT(allocator->top - (UintptrT)allocator->data + adjustment + size + sizeof(FE_MemoryStackAllocatorHeader) <= allocator->size, "not enough space to allocate memory")
	FE_CORE_ASSERT(allocator->top - (UintptrT)allocator->data + size + sizeof(FE_MemoryStackAllocatorHeader) <= allocator->size, "not enough space to allocate memory")
	//allocator->top += adjustment + size + sizeof(FE_MemoryStackAllocatorHeader);
	allocator->top = alignedAddress + size + sizeof(FE_MemoryStackAllocatorHeader);
	FE_MemoryStackAllocatorHeader* header = (FE_MemoryStackAllocatorHeader*)(allocator->top - sizeof(FE_MemoryStackAllocatorHeader));
	//header->blockStart = (void*)(alignedAddress - adjustment);
	header->blockStart = (void*)(alignedAddress);

	return (void*)alignedAddress;
}

void FE_API FE_MemoryStackAllocatorFree(FE_MemoryStackAllocator* allocator)
{
	FE_MemoryStackAllocatorHeader* header = (FE_MemoryStackAllocatorHeader*)(allocator->top - sizeof(FE_MemoryStackAllocatorHeader));
	allocator->top = (UintptrT)header->blockStart;
}

void FE_API FE_MemoryStackAllocatorClear(FE_MemoryStackAllocator* allocator)
{
	allocator->data = NULL;
	allocator->top = 0;
	allocator->size = 0;
}

void FE_MemoryStackAllocatorReset(FE_MemoryStackAllocator* allocator)
{
	allocator->top = (UintptrT)allocator->data;
}