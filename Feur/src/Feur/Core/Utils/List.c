#include "fepch.h"
#include "Feur/Core/Utils/List.h"

Bool FE_API FE_ListInit_impl(FE_List_impl* list, Byte** data)
{
	list->count = 0;
	list->capacity = 0;
	*data = NULL;
	list->isInitialized = TRUE;

	return TRUE;
}

Bool FE_API FE_ListPop_impl(FE_List_impl* list, Byte** data)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && *data != NULL && list->isInitialized == TRUE, "list or data is null or list hasn't been initialized");

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

Bool FE_ListRemove_impl(FE_List_impl* list, Byte** data, Uint32 id, SizeT dataSize)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && *data != NULL && list->isInitialized == TRUE, "list or data is null or list hasn't been initialized");

	
	if (list == NULL || NULL == data) return FALSE;

	Uint32 nextId = id + 1;

	memcpy((*data) + dataSize * id, (*data) + dataSize * nextId, ((list->count - 1) - id) * dataSize);

	list->count--;

	return TRUE;
}

Bool FE_API FE_ListInsert_impl(FE_List_impl* list, Byte** data, const void* value, Uint32 position, SizeT dataSize)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && list->isInitialized == TRUE, "list or data is null or list hasn't been initialized");
	if (list == NULL || data == NULL || *data == NULL || position > list->count - 1) return FALSE;

	Byte* temp = *data;

	if (list->capacity < list->count + 1)
	{
		list->capacity = list->count + 1;
		*data = FE_MemoryGeneralRealloc(*data, list->capacity * dataSize);
	}

	if (*data == NULL)
	{
		*data = temp;
		return FALSE;
	}


	//data[dataSize * (list->count - 1)] = NULL;
	
	SizeT bytePos = dataSize * position;
	
	//for (SizeT i = dataSize * (list->count+1); i > bytePos; i--) //move data to the end of the array
	//{
	//	*((*data) + i) = *((*data) + (i - dataSize));
	//}

	for (SizeT i = dataSize * list->count; i > bytePos; i -= dataSize)// it does not iterate on Byte* because it's less optimized du to compiler optimization, pointer calculation, ...
	{
		memcpy((*data) + i, (*data) + (i - dataSize), dataSize);
	}

	list->count++;
	
	memcpy((*data) + dataSize * position, value, dataSize);

	return TRUE;
}


//Bool FE_API FE_ListPush_impl(FE_List_impl* list, Byte** data, const void* value, SizeT dataSize)
//{
//	FE_CORE_ASSERT(list != NULL && data != NULL && list->isInitialized == TRUE, "list or data is null or list hasn't been initialized");
//	if (list == NULL) return FALSE;
//
//	Byte* temp = *data;
//
//	if (list->capacity <= list->count)
//	{
//		if (*data == NULL)
//		{
//			list->capacity += 1;
//			(*data) = FE_MemoryGeneralAlloc(dataSize * list->capacity);
//		}
//		else
//		{
//			list->capacity += list->capacity / 2;
//			(*data) = FE_MemoryGeneralRealloc((*data), dataSize * list->capacity);
//		}
//	}
//
//	if ((*data) == NULL)
//	{
//		(*data) = temp;
//		return FALSE;
//	}
//
//	SizeT lastItemId = list->count;
//	list->count++;
//
//	memcpy((*data) + dataSize * lastItemId, value, dataSize);
//
//	return TRUE;
//}

Bool FE_API FE_ListPushArray_impl(FE_List_impl* list, Byte** data, const void* arrayData, SizeT sizeToPush, SizeT dataSize)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && arrayData != NULL && sizeToPush > 0 && list->isInitialized == TRUE, "list or data is null or list hasn't been initialized");
	if (list == NULL || data == NULL) return FALSE;

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
	memcpy((*data) + dataSize * lastItemId, arrayData, dataSize * sizeToPush);

	return TRUE;
}


Bool FE_API FE_ListReserve_impl(FE_List_impl* list, Byte** data, SizeT amount, SizeT dataSize)
{
	FE_CORE_ASSERT(list != NULL && data != NULL, "list or data is null");
	if (list == NULL || data == NULL) return FALSE;

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

Bool FE_API FE_ListClear_impl(FE_List_impl* list, Byte** data)
{
	if (list == NULL || data == NULL || (*data) == NULL) return FALSE;

	list->capacity = 0;
	list->count = 0;
	FE_MemoryGeneralFree(*data);
	return TRUE;
}

Bool FE_ListRemoveDuplicate_impl(FE_List_impl* list, Byte** data, SizeT dataSize)
{
	FE_CORE_ASSERT(list != NULL && data != NULL, "list or data is null");
	if (list == NULL || list->count < 2 || data == NULL || (*data) == NULL) return FALSE;

	Bool isSame;
	for (Uint32 i = 0; i < list->count; i++)
	{
		for (Uint32 y = i + 1; y < list->count; y++)
		{
			isSame = TRUE;

			isSame = memcmp((*data) + i * dataSize, (*data) + y * dataSize, dataSize) == 0;
			/*for (Uint32 b = 0; b < dataSize; b++) for loop equivalent (barely) to memcmp
			{
				if ((*data)[i * dataSize + b] != (*data)[y * dataSize + b])
				{
					isSame = FALSE;
					break;
				}
			}*/

			if (isSame)
			{
				FE_ListRemove_impl(list, data, y, dataSize);
			}
		}
	}

	return TRUE;
}
