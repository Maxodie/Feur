#pragma once

typedef struct FE_List_impl {
    SizeT count;
    SizeT dataSize;
    SizeT capacity;
    //add capacity to prealloc 
} FE_List_impl;

#define FE_List(type) struct { FE_List_impl impl; type* data; }
//with 'a' an FE_List(type)
#define FE_ListCreate(a) FE_ListCreate_impl(&a.impl, a.impl.count, sizeof(*a.data))
//with 'a' an FE_List(type)
#define FE_ListPop(a) FE_ListPop_impl(&a.impl, &a.data)
//with 'a' an FE_List(type); 'value' type of 'type'; 'position' is Uint32
#define FE_ListInsert(a, value, position) FE_ListInsert_impl(&a.impl, &a.data, &value, position)
//with 'a' an FE_List(type); 'value' type of 'type'
#define FE_ListPush(a, value) FE_ListPush_impl(&a.impl, &a.data, &value)
//with 'a' an FE_List(type); 'value' type of 'type' it reserve a supplement : list.count += amount
#define FE_ListReserve(a, amount) FE_ListReserve_impl(&a.impl, &a.data, amount)

// TODO : Canva layer handling

FE_FORCEINLINE_FUN Bool FE_API FE_ListCreate_impl(FE_List_impl* list, SizeT count, SizeT dataSize);
Bool FE_API FE_ListPop_impl(FE_List_impl* list, Byte** data);
Bool FE_API FE_ListInsert_impl(FE_List_impl* list, Byte** data, void* value, Uint32 position);
Bool FE_API FE_ListPush_impl(FE_List_impl* list, Byte** data, void* value); 

Bool FE_API FE_ListReserve_impl(FE_List_impl* list, Byte** data, SizeT amount);