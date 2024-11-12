#include "fepch.h"
#include "FreeListAllocator.h"

void FE_DECL FE_MemoryFreeListAllocatorInit(FE_MemoryFreeListAllocator* allocator, SizeT size, const void* start)
{
	FE_CORE_ASSERT(size > sizeof(FreeBlock), "size is too small (less than sizeof(FreeBlock) or 16 bytes)");
    allocator->freeBlocks = (FreeBlock*)start;
	allocator->freeBlocks->size = size;
	allocator->freeBlocks->next = NULL;
}

void FE_DECL FE_MemoryFreeListAllocatorShutdown(FE_MemoryFreeListAllocator* allocator)
{
    allocator->freeBlocks = NULL;
}


void* FE_DECL FE_MemoryFreeListAllocatorAlloc(FE_MemoryFreeListAllocator* allocator, SizeT size, Uint8 alignment)
{
    FE_CORE_ASSERT(size != 0 && alignment != 0, "Size and alignement can not be 0");
    FreeBlock* prevFreeBlock = NULL;
    FreeBlock* currentFreeBlock = allocator->freeBlocks;

    while (currentFreeBlock != NULL)
    {
        //Calculate adjustment needed to keep object correctly aligned 
        UintptrT adjustment = FE_MemoryAlignForwardAdjustmentWithHeader((UintptrT)currentFreeBlock, alignment, sizeof(FreeListAllocationHeader));
        size_t total_size = size + adjustment;

        //If allocation doesn't fit in this FreeBlock, try the next 
        if (currentFreeBlock->size < total_size)
        {
            prevFreeBlock = currentFreeBlock;
            currentFreeBlock = currentFreeBlock->next;
            continue;
        }

        FE_STATIC_ASSERT(sizeof(FreeListAllocationHeader) >= sizeof(FreeBlock), "sizeof(AllocationHeader) < sizeof(FreeBlock)");

        //If allocations in the remaining memory will be impossible 
        if (currentFreeBlock->size - total_size <= sizeof(FreeListAllocationHeader))
        {
            //Increase allocation size instead of creating a new FreeBlock 
            total_size = currentFreeBlock->size;

            if (prevFreeBlock != NULL)
                prevFreeBlock->next = currentFreeBlock->next;
            else
                allocator->freeBlocks = currentFreeBlock->next;
        }
        else
        {
            //Else create a new FreeBlock containing remaining memory 
            FreeBlock* next_block = (FreeBlock*)(currentFreeBlock + total_size);

            next_block->size = currentFreeBlock->size - total_size;
            next_block->next = currentFreeBlock->next;

            if (prevFreeBlock != NULL)
                prevFreeBlock->next = next_block;
            else
                allocator->freeBlocks = next_block;
        }

        UintptrT aligned_address = (UintptrT)currentFreeBlock + adjustment;
        FreeListAllocationHeader* header = (FreeListAllocationHeader*)(aligned_address - sizeof(FreeListAllocationHeader));
        header->size = total_size;
        header->adjustment = adjustment;

        FE_CORE_ASSERT(FE_MemoryAlignForwardAdjustment((UintptrT)aligned_address, alignment) == 0, "alignment should be 0");

        return (void*)aligned_address;
    }

    FE_CORE_ASSERT(FALSE, "there are no free blocks left to store the data")
    return NULL;
}

void FE_DECL FE_MemoryFreeListAllocatorFree(FE_MemoryFreeListAllocator* allocator, void* ptr)
{
    FE_CORE_ASSERT(ptr != NULL, "Given pointer is NULL");
    FreeListAllocationHeader* header = (FreeListAllocationHeader*)((UintptrT)ptr - sizeof(FreeListAllocationHeader));
    UintptrT block_start = (UintptrT)ptr - header->adjustment;
    SizeT block_size = header->size;
    UintptrT block_end = block_start + block_size;
    FreeBlock* prevFreeBlock = NULL;
    FreeBlock* currentFreeBlock = allocator->freeBlocks;

    while (currentFreeBlock != NULL)
    {
        if ((UintptrT)currentFreeBlock >= block_end) break;
        prevFreeBlock = currentFreeBlock;
        currentFreeBlock = currentFreeBlock->next;
    }

    FE_CORE_ASSERT((FreeBlock*)block_start != NULL && ((FreeBlock*)block_start)->size > 0, "the pointer %p shouldn't have been freed", ptr);

    if (prevFreeBlock == NULL)
    {
        prevFreeBlock = (FreeBlock*)block_start;
        prevFreeBlock->size = block_size; // throw an error here means that some things shouldn't have been freed
        prevFreeBlock->next = allocator->freeBlocks;
        allocator->freeBlocks = prevFreeBlock;
    }
    else if ((UintptrT)prevFreeBlock + prevFreeBlock->size == block_start)
    {
        prevFreeBlock->size += block_size;
    }
    else
    {
        FreeBlock* temp = (FreeBlock*)block_start;
        temp->size = block_size;
        temp->next = prevFreeBlock->next;
        prevFreeBlock->next = temp;
        prevFreeBlock = temp;
    }

    if (currentFreeBlock != NULL && (UintptrT)currentFreeBlock == block_end)
    {
        prevFreeBlock->size += currentFreeBlock->size;
        prevFreeBlock->next = currentFreeBlock->next;
    }
}

void* FE_DECL FE_MemoryFreeListAllocatorRealloc(FE_MemoryFreeListAllocator* allocator, void* ptr, SizeT size, Uint8 alignment)
{
    FE_CORE_ASSERT(ptr != NULL, "the given pointer is NULL")
    FreeListAllocationHeader* header = (FreeListAllocationHeader*)((UintptrT)ptr - sizeof(FreeListAllocationHeader));
    void* result = FE_MemoryFreeListAllocatorAlloc(allocator, size, alignment);

    memcpy(result, ptr, header->size < size ? header->size : size);

    FE_MemoryFreeListAllocatorFree(allocator, ptr);

    return result;
}
