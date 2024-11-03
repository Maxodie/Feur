#include "fepch.h"
#include "Feur/Core/Utils/List.h"

FE_FORCEINLINE_FUN Bool FE_API FE_ListInit_impl(FE_List_impl* list, Byte** data)
{
	list->count = 0;
	list->capacity = 0;
	*data = NULL;
	list->isInitialized = TRUE;

	return TRUE;
}

Bool FE_API FE_ListPop_impl(FE_List_impl* list, Byte** data)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && *data != NULL && list->isInitialized == TRUE, "FE_ListPop_impl list or data is null or list hasn't been initialized");

	if (list == NULL || NULL == data) return FALSE;
	
	list->count--;

	/*if (list->count == 0)
	{
		FE_MemoryGeneralFree(data);
		return;
	}*/

	/*Byte** temp = *data;
	*data = FE_MemoryGeneralRealloc(*data, (list->count) * list->dataSize);
	if (*data == NULL)
	{
		*data = temp;
		return FALSE;
	}*/

	return TRUE;
}

Bool FE_API FE_ListInsert_impl(FE_List_impl* list, Byte** data, const void* value, Uint32 position, SizeT dataSize)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && list->isInitialized == TRUE, "FE_ListPop_impl list or data is null or list hasn't been initialized");
	if (list == NULL || NULL == *data || position > list->count) return FALSE;

	SizeT i;
	Byte* temp = *data;

	if (list->capacity < list->count + 1)
	{
		*data = FE_MemoryGeneralRealloc(*data, (list->count + 1) * dataSize);
	}

	if (*data == NULL)
	{
		*data = temp;
		return FALSE;
	}

	list->count++;

	data[dataSize * (list->count - 1)] = NULL;

	for (i = list->count - 1; i >= position; i--)
	{
		data[dataSize * i] = data[dataSize * (i - 1)];
	}

	SizeT positionItemId = (SizeT)position - 1;
	memcpy(((*data) + dataSize * positionItemId), value, dataSize);

	return TRUE;
}


Bool FE_API FE_ListPush_impl(FE_List_impl* list, Byte** data, const void* value, SizeT dataSize)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && list->isInitialized == TRUE, "FE_ListPop_impl list or data is null or list hasn't been initialized");
	if (list == NULL) return FALSE;

	Byte* temp = *data;

	if (list->capacity <= list->count)
	{
		if (*data == NULL)
		{
			list->capacity += 1;
			(*data) = FE_MemoryGeneralAlloc(dataSize * list->capacity);
		}
		else
		{
			list->capacity += list->capacity / 2;
			(*data) = FE_MemoryGeneralRealloc((*data), dataSize * list->capacity);
		}
	}

	if ((*data) == NULL)
	{
		(*data) = temp;
		return FALSE;
	}

	SizeT lastItemId = list->count;
	list->count++;

	memcpy(((*data) + dataSize * lastItemId), value, dataSize);

	return TRUE;
}

Bool FE_ListPushArray_impl(FE_List_impl* list, Byte** data, const void* arrayData, SizeT sizeToPush, SizeT dataSize)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && arrayData != NULL && sizeToPush > 0 && list->isInitialized == TRUE, "FE_ListPop_impl list or data is null or list hasn't been initialized");
	if (list == NULL) return FALSE;

	Byte* temp = *data;

	if (list->capacity <= sizeToPush)
	{
		if (*data == NULL)
		{
			list->capacity += sizeToPush;
			(*data) = FE_MemoryGeneralAlloc(dataSize * list->capacity);
		}
		else
		{
			list->capacity += sizeToPush + llabs(list->capacity / 2 - sizeToPush);
			(*data) = FE_MemoryGeneralRealloc((*data), list->capacity * dataSize);
		}
	}

	if ((*data) == NULL)
	{
		(*data) = temp;
		return FALSE;
	}

	SizeT lastItemId = list->count;
	list->count += sizeToPush;
	memcpy(((*data) + dataSize * lastItemId), arrayData, dataSize * sizeToPush);

	return TRUE;
}


Bool FE_API FE_ListReserve_impl(FE_List_impl* list, Byte** data, SizeT amount, SizeT dataSize)
{
	FE_CORE_ASSERT(list != NULL && data != NULL, "FE_ListPop_impl list or data is null");
	if (list == NULL) return FALSE;

	list->capacity += amount;

	Byte* temp = *data;

	(*data) = (*data) == NULL ?
		FE_MemoryGeneralAlloc(dataSize * list->capacity) :
		FE_MemoryGeneralRealloc((*data), dataSize * list->capacity);

	if ((*data) == NULL)
	{
		(*data) = temp;
		return FALSE;
	}

	return TRUE;
}

Bool FE_ListClear_impl(FE_List_impl* list, Byte** data)
{
	if (list == NULL || data == NULL || (*data) == NULL) return FALSE;

	list->capacity = 0;
	list->count = 0;
	FE_MemoryGeneralFree(*data);
	return TRUE;
}
