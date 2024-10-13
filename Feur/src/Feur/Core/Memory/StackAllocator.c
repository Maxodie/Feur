#include "fepch.h"
#include "Feur/Core/Memory/StackAllocator.h"

void FE_API FE_MemoryStackAllocatorInit(FE_MemoryStackAllocator* allocator, SizeT size)
{
	allocator->data = FE_MemoryCustomMalloc(size);
	allocator->top = (UintptrT)allocator->data;
	allocator->size = size;
}

void* FE_API FE_MemoryStackAllocatorAlloc(FE_MemoryStackAllocator* allocator, SizeT size, SizeT alignment)
{
	UintptrT adjustment = FE_MemoryAlignForwardAdjustment(allocator->top, alignment);
	UintptrT alignedAddress = adjustment + allocator->top;

	FE_CORE_ASSERT(allocator->top - (UintptrT)allocator->data + adjustment + size + sizeof(FE_MemoryStackAllocatorHeader) <= allocator->size, "not enough space to allocate memory")
	allocator->top += adjustment + size + sizeof(FE_MemoryStackAllocatorHeader);
	FE_MemoryStackAllocatorHeader* header = (FE_MemoryStackAllocatorHeader*)(allocator->top - sizeof(FE_MemoryStackAllocatorHeader));
	header->blockStart = (void*)(alignedAddress - adjustment);

	return (void*)alignedAddress;
}

void FE_API FE_MemoryStackAllocatorFree(FE_MemoryStackAllocator* allocator)
{
	FE_MemoryStackAllocatorHeader* header = (FE_MemoryStackAllocatorHeader*)(allocator->top - sizeof(FE_MemoryStackAllocatorHeader));
	allocator->top = (UintptrT)header->blockStart;
}

void FE_API FE_MemoryStackAllocatorClear(FE_MemoryStackAllocator* allocator)
{
	free(allocator->data);
	allocator->data = NULL;
	allocator->top = 0;
	allocator->size = 0;
}

void FE_MemoryStackAllocatorReset(FE_MemoryStackAllocator* allocator)
{
	allocator->top = (UintptrT)allocator->data;
}

void FE_API FE_MemoryStackAllocatorPrint(FE_MemoryStackAllocator* allocator)
{
	FE_CORE_LOG_DEBUG("Stack Allocator : Size %zu    ||    Capacity : %zu    ||    (local)Base ptr : %p    ||    (local)Top ptr : %p", 
		(SizeT)(allocator->top - (UintptrT)allocator->data ),
		allocator->size, 
		NULL, 
		allocator->top - (UintptrT)allocator->data);
	/*
	FE_MemoryStack* current = FE_MemoryStackHead();

	size_t id = 0;
	size_t totalSize = 0;
	while (current != NULL)
	{
		FE_CORE_LOG_DEBUG("id : %zu    ||    Capacity : %zu    ||    Data : %p    ||    Next : %p    ||    Size : %zu", id, current->capacity, current->data, current->next, current->size);
		totalSize += current->capacity;

		current = current->next;
		id++;
	}
	FE_CORE_LOG_DEBUG("MemoryStackAllocator.c:: FE_MemoryStackAllocatorPrint : Total memory arena size : %zu", totalSize);*/
}
