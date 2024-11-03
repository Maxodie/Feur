#pragma once

typedef struct FE_List_impl {
    SizeT count;
    SizeT capacity;
    Bool isInitialized;
} FE_List_impl;

//FE_List must be freed with FE_ListClear(a)
#define FE_List(type) struct { FE_List_impl impl; type* data; }
//with 'fe_list' an FE_List(type)
#define FE_ListInit(fe_list) FE_ListInit_impl(&fe_list.impl, (Byte**)&fe_list.data)
//with 'fe_list' an FE_List(type)
#define FE_ListPop(fe_list) FE_ListPop_impl(&fe_list.impl, (Byte**)&fe_list.data)
//with 'fe_list' an FE_List(type); 'value' type of 'type'; 'position' is Uint32
#define FE_ListInsert(fe_list, value, position) FE_ListInsert_impl(&fe_list.impl, (Byte**)&fe_list.data, (const void*)&value, position, sizeof(*fe_list.data))
//with 'fe_list' an FE_List(type); 'value' type of 'type'
#define FE_ListPush(fe_list, value) FE_ListPushArray_impl(&fe_list.impl, (Byte**)&fe_list.data, (const void*)&value, 1, sizeof(*fe_list.data))
//#define FE_ListPush(fe_list, value) FE_ListPush_impl(&fe_list.impl, (Byte**)&fe_list.data, (const void*)&value, sizeof(*fe_list.data))
//with 'fe_list' an FE_List(type); 'value' type of 'type'
#define FE_ListPushArray(fe_list, arrayDataPtr, sizeToPush) FE_ListPushArray_impl(&fe_list.impl, (Byte**)&fe_list.data, (const void*)arrayDataPtr, sizeToPush, sizeof(*fe_list.data))
//with 'fe_list' an FE_List(type); 'value' type of 'type' it reserve a supplement : list.count += amount
#define FE_ListReserve(fe_list, amount) FE_ListReserve_impl(&fe_list.impl, (Byte**)&fe_list.data, amount, sizeof(*fe_list.data))
//with 'fe_list' an FE_List(type);
#define FE_ListClear(fe_list) FE_ListClear_impl(&fe_list.impl, (Byte**)&fe_list.data)

Bool FE_API FE_ListInit_impl(FE_List_impl* list, Byte** data);
Bool FE_API FE_ListPop_impl(FE_List_impl* list, Byte** data);

Bool FE_API FE_ListInsert_impl(FE_List_impl* list, Byte** data, const void* value, Uint32 position, SizeT dataSize);

Bool FE_API FE_ListPush_impl(FE_List_impl* list, Byte** data, const void* value, SizeT dataSize);
Bool FE_API FE_ListPushArray_impl(FE_List_impl* list, Byte** data, const void* arrayData, SizeT sizeToPush, SizeT dataSize);

Bool FE_API FE_ListReserve_impl(FE_List_impl* list, Byte** data, SizeT amount, SizeT dataSize);
Bool FE_API FE_ListClear_impl(FE_List_impl* list, Byte** data); 