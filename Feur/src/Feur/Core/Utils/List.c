#include "fepch.h"
#include "Feur/Core/Utils/List.h"

FE_FORCEINLINE_FUN Bool FE_API FE_ListCreate_impl(FE_List_impl* list, SizeT count, SizeT dataSize)
{
    list->dataSize = dataSize;

	return TRUE;
}

Bool FE_API FE_ListPop_impl(FE_List_impl* list, Byte** data)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && *data != NULL, "FE_ListPop_impl list or data is null");

	if (list == NULL || NULL == data) return FALSE;
	
	list->count--;

	/*if (list->count == 0)
	{
		FE_MemoryGeneralFree(data);
		return;
	}*/

	/*Layer** temp = *data;
	*data = FE_MemoryGeneralRealloc(*data, (list->count) * list->dataSize);
	if (*data == NULL)
	{
		*data = temp;
		return FALSE;
	}*/

	return TRUE;
}

Bool FE_API FE_ListInsert_impl(FE_List_impl* list, Byte** data, void* value, Uint32 position)
{
	FE_CORE_ASSERT(list != NULL && data != NULL, "FE_ListPop_impl list or data is null");
	if (list == NULL || NULL == *data || position > list->count) return FALSE;

	SizeT i;
	Layer** temp = *data;

	*data = FE_MemoryGeneralRealloc(*data, (list->count + 1) * list->dataSize);

	if (*data == NULL)
	{
		*data = temp;
		return FALSE;
	}

	list->count++;

	(*data)[list->dataSize * (list->count - 1)] = NULL;

	for (i = list->count - 1; i >= position; i--)
	{
		(*data)[list->dataSize * i] = (*data)[list->dataSize * (i - 1)];
	}

	SizeT positionItemId = (SizeT)position - 1;
	memcpy(((*data) + list->dataSize * positionItemId), value, list->dataSize);

	return TRUE;
}

Bool FE_API FE_ListPush_impl(FE_List_impl* list, Byte** data, void* value)
{
	FE_CORE_ASSERT(list != NULL && data != NULL, "FE_ListPop_impl list or data is null");
	if (list == NULL) return FALSE;

	Layer** temp = *data;

	if (list->capacity <= list->count)
	{
		list->capacity += list->capacity == 0 ? 1 : list->capacity / 2;
		(*data) = list->capacity == 0 ?
			FE_MemoryGeneralAlloc(list->dataSize * list->capacity) :
			FE_MemoryGeneralRealloc((*data), list->dataSize * list->capacity);
	}

	if ((*data) == NULL)
	{
		(*data) = temp;
		return FALSE;
	}

	SizeT lastItemId = list->count;
	list->count++;

	memcpy(((*data) + list->dataSize * lastItemId), value, list->dataSize);

	return TRUE;
}

Bool FE_API FE_ListReserve_impl(FE_List_impl* list, Byte** data, SizeT amount)
{
	FE_CORE_ASSERT(list != NULL && data != NULL, "FE_ListPop_impl list or data is null");
	if (list == NULL) return FALSE;

	list->capacity += amount;

	Layer** temp = *data;

	(*data) = (*data) == NULL ?
		FE_MemoryGeneralAlloc(list->dataSize * list->capacity) :
		FE_MemoryGeneralRealloc((*data), list->dataSize * list->capacity);

	if ((*data) == NULL)
	{
		(*data) = temp;
		return FALSE;
	}

	return TRUE;
}
