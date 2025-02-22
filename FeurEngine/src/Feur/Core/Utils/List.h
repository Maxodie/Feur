#pragma once

typedef struct FE_List_impl {
    SizeT count;
    SizeT capacity;
    Bool isInitialized;
    void* head;
} FE_List_impl;

//FE_List must be freed with FE_ListClear(a)
#define FE_List(type)  struct { FE_List_impl impl; type* data; }
//with 'fe_list' an FE_List(type)
#define FE_ListGet(fe_list, id) FE_ListGet_imp(&(fe_list).impl, (Byte*)fe_list.data, id, sizeof(*(fe_list).data))

//Put list as a parameter
#define FE_ListParameterPtr(type) FE_List_impl*
#define FE_ListFromParameterPtr(parameter) { *parameter, parameter->head }
////Convert list parameter to FE_List(type)
//#define FE_ListParameterRead(newVariable, parameterPtrVariableName, type) FE_List(type) newVariable = { impl_list_##parameterPtrVariableName, data_list_##parameterPtrVariableName }


//with 'fe_list' an FE_List(type)
#define FE_ListInit(fe_list) FE_CORE_ASSERT(FE_ListInit_impl(&(fe_list).impl, (Byte**)&(fe_list).data), "failed to init fe_list")
//with 'fe_list' an FE_List(type)
#define FE_ListPop(fe_list) FE_CORE_ASSERT(FE_ListPop_impl(&(fe_list).impl, (Byte**)&(fe_list).data), "failed to pop fe_list")
//with 'fe_list' an FE_List(type); 'id' the item id to remove
#define FE_ListRemoveAt(fe_list, id) FE_CORE_ASSERT(FE_ListRemoveAt_impl(&(fe_list).impl, (Byte**)&(fe_list).data, id, sizeof(*(fe_list).data)), "failed to removeAt fe_list")
//with 'fe_list' an FE_List(type); 'value' the value to remove; don't work with char*; return index of the item removed
#define FE_ListRemove(fe_list, value) FE_ListRemove_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)&value, sizeof(*(fe_list).data))
//with 'fe_list' an FE_List(type); 'value' type of 'type'; 'position' is Uint32
#define FE_ListInsert(fe_list, value, position) FE_CORE_ASSERT(FE_ListInsert_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)&value, position, sizeof(*(fe_list).data)), "failed to insert fe_list")

//with 'fe_list' an FE_List(type); 'type' same type of *fe_list.data; 'value' type of 'type'; 'position' is Uint32
#define FE_ListInsertValue(fe_list, type, value, position) { \
type temp = value; \
FE_ListInsert_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)&value, position, sizeof(*(fe_list).data)) \
}


//with 'fe_list' an FE_List(type); 'value' type of 'type'
#define FE_ListPush(fe_list, value)  FE_CORE_ASSERT(FE_ListPushArray_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)&value, 1, sizeof(*(fe_list).data)), "failed to push fe_list")

//#define FE_ListPush(fe_list, value) FE_ListPush_impl(&fe_list.impl, (Byte**)&fe_list.data, (const void*)&value, sizeof(*fe_list.data))
//with 'fe_list' an FE_List(type); 'type' same type of *fe_list.data; 'value' type of 'type';
#define FE_ListPushValue(fe_list, type, value) { \
type temp = value; \
FE_CORE_ASSERT(FE_ListPushArray_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)&temp, 1, sizeof(*(fe_list).data)), "failed to push value fe_list"); \
}
//with 'fe_list' an FE_List(type); 'value' type of 'type'
#define FE_ListPushArray(fe_list, arrayDataPtr, countToPush) FE_CORE_ASSERT(FE_ListPushArray_impl(&(fe_list).impl, (Byte**)&(fe_list).data, (const void*)arrayDataPtr, countToPush, sizeof(*(fe_list).data)), "failed to push array fe_list")
//with 'fe_list' an FE_List(type); 'value' type of 'type' it reserve a supplement : list.capacity += amount
#define FE_ListReserve(fe_list, amount) FE_CORE_ASSERT(FE_ListReserve_impl(&(fe_list).impl, (Byte**)&(fe_list).data, amount, sizeof(*(fe_list).data)), "failed to reserve fe_list")
//with 'fe_list' an FE_List(type); 'value' type of 'type' it reserve a supplement : list.capacity += amount and list.count += amount
#define FE_ListResize(fe_list, amount) FE_CORE_ASSERT(FE_ListResize_impl(&(fe_list).impl, (Byte**)&(fe_list).data, amount, sizeof(*(fe_list).data)), "failed to resize fe_list")
//with 'fe_list' an FE_List(type);
#define FE_ListClear(fe_list) FE_CORE_ASSERT(FE_ListClear_impl(&(fe_list).impl, (Byte**)&(fe_list).data), "failed to clear fe_list")
//with 'fe_list' an FE_List(type);
#define FE_ListRemoveDuplicate(fe_list) FE_CORE_ASSERT(FE_ListRemoveDuplicate_impl(&(fe_list).impl, (Byte**)&(fe_list).data, sizeof(*(fe_list).data)), "failed to remove duplicate fe_list")
//with 'fe_listA' an FE_List(type); 'fe_listB' an FE_List(type);
#define FE_ListEqual(fe_listA, fe_listB) FE_ListEqual_impl(&(fe_listA).impl, &(fe_listB).impl, (Byte**)&(fe_listA).data, (Byte**)&(fe_listB).data, sizeof(*(fe_list).data))

//with 'fe_list' an FE_List(type);
#define FE_ListRemoveAll(fe_list) FE_CORE_ASSERT(FE_ListRemoveAll_impl(&(fe_list).impl), "failed to set count")

//with 'fe_list' an FE_List(type);
#define FE_ListPrint(fe_list) FE_ListPrint_impl(&(fe_list).impl, (Byte**)&(fe_list).data, sizeof(*(fe_list).data))


Bool FE_DECL FE_ListInit_impl(FE_List_impl* list, Byte** data);
void* FE_DECL FE_ListGet_imp(FE_List_impl* list, Byte* data, SizeT id, SizeT dataSize);

Bool FE_DECL FE_ListPop_impl(FE_List_impl* list, Byte** data);
Int64 FE_DECL FE_ListRemove_impl(FE_List_impl* list, Byte** data, const void* value, SizeT dataSize);
Bool FE_DECL FE_ListRemoveAt_impl(FE_List_impl* list, Byte** data, Uint32 id, SizeT dataSize);

Bool FE_DECL FE_ListInsert_impl(FE_List_impl* list, Byte** data, const void* value, Uint32 position, SizeT dataSize);

//Bool FE_DECL FE_ListPush_impl(FE_List_impl* list, Byte** data, const void* value, SizeT dataSize);
Bool FE_DECL FE_ListPushArray_impl(FE_List_impl* list, Byte** data, const void* arrayData, SizeT countToPush, SizeT dataSize);

Bool FE_DECL FE_ListReserve_impl(FE_List_impl* list, Byte** data, SizeT amount, SizeT dataSize);
Bool FE_DECL FE_ListResize_impl(FE_List_impl* list, Byte** data, SizeT amount, SizeT dataSize);
Bool FE_DECL FE_ListClear_impl(FE_List_impl* list, Byte** data);

Bool FE_DECL FE_ListRemoveDuplicate_impl(FE_List_impl* list, Byte** data, SizeT dataSize);

Bool FE_DECL FE_ListEqual_impl(FE_List_impl* listA, FE_List_impl* listB, Byte** dataA, Byte** dataB, SizeT dataSize);

Bool FE_DECL FE_ListRemoveAll_impl(FE_List_impl* list);

void FE_DECL FE_ListPrint_impl(const FE_List_impl* list, const Byte* data, SizeT dataSize);
void FE_DECL FE_ListPrintReport();
