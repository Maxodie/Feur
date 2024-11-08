#pragma once

typedef struct FE_List_impl {
    SizeT count;
    SizeT capacity;
    Bool isInitialized;
} FE_List_impl;

//FE_List must be freed with FE_ListClear(a)
#  define FE_List(type)  struct { FE_List_impl impl; type* data; }

//with 'fe_list' an FE_List(type)
#define FE_ListInit(fe_list) FE_ListInit_impl(&(fe_list).impl, (Byte**)&(fe_list).data)
//with 'fe_list' an FE_List(type)
#define FE_ListPop(fe_list) FE_ListPop_impl(&(fe_list).impl, (Byte**)&(fe_list).data)
//with 'fe_list' an FE_List(type); 'id' the item id to remove
#define FE_ListRemoveAt(fe_list, id) FE_ListRemoveAt_impl(&(fe_list).impl, (Byte**)&(fe_list).data, id, sizeof(*(fe_list).data))
//with 'fe_list' an FE_List(type); 'value' the value to remove; don't work with char*
#define FE_ListRemove(fe_list, value) FE_ListRemove_impl(&(fe_list).impl, (Byte**)&(fe_list).data, value, sizeof(*(fe_list).data))
//with 'fe_list' an FE_List(type); 'value' type of 'type'; 'position' is Uint32
#define FE_ListInsert(fe_list, value, position) FE_ListInsert_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)&value, position, sizeof(*(fe_list).data))

//with 'fe_list' an FE_List(type); 'type' same type of *fe_list.data; 'value' type of 'type'; 'position' is Uint32
#define FE_ListInsertValue(fe_list, type, value, position) { \
type temp = value; \
FE_ListInsert_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)&value, position, sizeof(*(fe_list).data)) \
}


//with 'fe_list' an FE_List(type); 'value' type of 'type'
#define FE_ListPush(fe_list, value) FE_ListPushArray_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)&value, 1, sizeof(*(fe_list).data))
//#define FE_ListPush(fe_list, value) FE_ListPush_impl(&fe_list.impl, (Byte**)&fe_list.data, (const void*)&value, sizeof(*fe_list.data))
//with 'fe_list' an FE_List(type); 'type' same type of *fe_list.data; 'value' type of 'type';
#define FE_ListPushValue(fe_list, type, value) { \
type temp = value; \
FE_ListPushArray_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)&temp, 1, sizeof(*(fe_list).data)); \
}
//with 'fe_list' an FE_List(type); 'value' type of 'type'
#define FE_ListPushArray(fe_list, arrayDataPtr, sizeToPush) FE_ListPushArray_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)arrayDataPtr, sizeToPush, sizeof(*(fe_list).data))
//with 'fe_list' an FE_List(type); 'value' type of 'type' it reserve a supplement : list.capacity += amount
#define FE_ListReserve(fe_list, amount) FE_ListReserve_impl(&(fe_list).impl, (Byte**)&(fe_list).data, amount, sizeof(*(fe_list).data))
//with 'fe_list' an FE_List(type); 'value' type of 'type' it reserve a supplement : list.capacity += amount and list.count += amount
#define FE_ListResize(fe_list, amount) FE_ListResize_impl(&(fe_list).impl, (Byte**)&(fe_list).data, amount, sizeof(*(fe_list).data))
//with 'fe_list' an FE_List(type);
#define FE_ListClear(fe_list) FE_ListClear_impl(&(fe_list).impl, (Byte**)&(fe_list).data)
//with 'fe_list' an FE_List(type);
#define FE_ListRemoveDuplicate(fe_list) FE_ListRemoveDuplicate_impl(&(fe_list).impl, (Byte**)&(fe_list).data, sizeof(*(fe_list).data))
//with 'fe_listA' an FE_List(type); 'fe_listB' an FE_List(type);
#define FE_ListEqual(fe_listA, fe_listB) FE_ListEqual_impl(&(fe_listA).impl, &(fe_listB).impl, (Byte**)&(fe_listA).data, (Byte**)&(fe_listB).data, sizeof(*(fe_list).data))

Bool FE_API FE_ListInit_impl(FE_List_impl* list, Byte** data);
Bool FE_API FE_ListPop_impl(FE_List_impl* list, Byte** data);
Bool FE_API FE_ListRemove_impl(FE_List_impl* list, Byte** data, const void* value, SizeT dataSize);
Bool FE_API FE_ListRemoveAt_impl(FE_List_impl* list, Byte** data, Uint32 id, SizeT dataSize);

Bool FE_API FE_ListInsert_impl(FE_List_impl* list, Byte** data, const void* value, Uint32 position, SizeT dataSize);

//Bool FE_API FE_ListPush_impl(FE_List_impl* list, Byte** data, const void* value, SizeT dataSize);
Bool FE_API FE_ListPushArray_impl(FE_List_impl* list, Byte** data, const void* arrayData, SizeT sizeToPush, SizeT dataSize);

Bool FE_API FE_ListReserve_impl(FE_List_impl* list, Byte** data, SizeT amount, SizeT dataSize);
Bool FE_API FE_ListResize_impl(FE_List_impl* list, Byte** data, SizeT amount, SizeT dataSize);
Bool FE_API FE_ListClear_impl(FE_List_impl* list, Byte** data); 

Bool FE_API FE_ListRemoveDuplicate_impl(FE_List_impl* list, Byte** data, SizeT dataSize);

Bool FE_API FE_ListEqual_impl(FE_List_impl* listA, FE_List_impl* listB, Byte** dataA, Byte** dataB, SizeT dataSize);

FE_API FE_ListPrintReport();