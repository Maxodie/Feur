#include "fepch.h"
#include "Feur/Core/Memory/PoolAllocator.h"

//@TODO add parameters to make a page system, divided in same allocation size pages
void FE_DECL FE_MemoryPoolAllocatorInit(FE_MemoryPoolAllocator* allocator, SizeT blockSize, SizeT chunkSize, SizeT alignment, const void* memory)
{
    FE_CORE_ASSERT(chunkSize >= sizeof(void*), "Pool Allocator minimum size required is 8 byts or sizeof(void*)");
    FE_CORE_ASSERT(blockSize % chunkSize == 0, "ChunkSize can not be divided by blockSize");

    allocator->freeData = (void**)((UintptrT)FE_MemoryAlignAddress((UintptrT)memory, alignment));
    
    SizeT numChunk = blockSize / chunkSize;
    void** it = allocator->freeData;

    //Initialize free blocks list 
    for (SizeT i = 0; i < numChunk - 1; i++)
    {
        *it = it + chunkSize; //can throw an error when trying to write '*it' (I don't know why)
        it += chunkSize;
    }

    allocator->chunkSize = chunkSize;
    *it = NULL;
}

void* FE_DECL FE_MemoryPoolAllocatorAlloc(FE_MemoryPoolAllocator* allocator, SizeT size)
{
    FE_CORE_ASSERT(size <= allocator->chunkSize, "size is too much for the pool allocation");
    FE_CORE_ASSERT(allocator->freeData != NULL, "free data is NULL, not enough chunks");

    void* ptr = allocator->freeData;
    allocator->freeData = (void**)(*allocator->freeData);
    return ptr;
}

void FE_DECL FE_MemoryPoolAllocatorFree(FE_MemoryPoolAllocator* allocator, void* ptr)
{
    *((void**)ptr) = allocator->freeData;
    allocator->freeData = (void**)(ptr);
}