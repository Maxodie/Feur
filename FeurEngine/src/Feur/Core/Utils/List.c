#include "fepch.h"
#include "Feur/Core/Utils/List.h"

#ifdef FE_DEBUG
Uint64 allocatedListCount = 0;
Uint64 freedListCount = 0;
#endif

Bool FE_DECL FE_ListCheck(FE_List_impl* list, Byte** data)
{
	return list != NULL && NULL != data && list->isInitialized == TRUE;
}

Bool FE_DECL FE_ListInit_impl(FE_List_impl* list, Byte** data)
{
	list->count = 0;
	list->capacity = 0;
	*data = NULL;
	list->isInitialized = TRUE;
	list->head = NULL;

	return TRUE;
}

Bool FE_DECL FE_ListPop_impl(FE_List_impl* list, Byte** data)
{
	if (!FE_ListCheck(list, data))
	{
		FE_CORE_LOG_ERROR("failed to pop");
		return FALSE;
	}
	
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

Int64 FE_ListRemove_impl(FE_List_impl* list, Byte** data, const void* value, SizeT dataSize)
{
	if (!FE_ListCheck(list, data) || *data == NULL)
	{
		FE_CORE_LOG_ERROR("failed to remove ptr %p", value);
		return -1;
	}

	Uint32 id = 0;
	Bool isFound = FALSE;
	for (id; id < list->count; id++)
	{
		isFound = memcmp((*data) + id * dataSize, value, dataSize) == 0;
		if (isFound) break;
	}

	if (!isFound) return -1;

	Uint32 nextId = id + 1;

	memcpy((*data) + dataSize * id, (*data) + dataSize * nextId, ((list->count - 1) - id) * dataSize);

	list->count--;

	return id;
}

Bool FE_ListRemoveAt_impl(FE_List_impl* list, Byte** data, Uint32 id, SizeT dataSize)
{
	if (!FE_ListCheck(list, data) || *data == NULL)
	{
		FE_CORE_LOG_ERROR("failed to remove at %d", id);
		return FALSE;
	}

	Uint32 nextId = id + 1;

	memcpy((*data) + dataSize * id, (*data) + dataSize * nextId, ((list->count - 1) - id) * dataSize);

	list->count--;

	return TRUE;
}

Bool FE_DECL FE_ListInsert_impl(FE_List_impl* list, Byte** data, const void* value, Uint32 position, SizeT dataSize)
{
	if (!FE_ListCheck(list, data) || *data == NULL || position > list->count - 1)
	{
		FE_CORE_LOG_ERROR("failed to insert ptr %p at %d", value, position);
		return FALSE;
	}

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


//Bool FE_DECL FE_ListPush_impl(FE_List_impl* list, Byte** data, const void* value, SizeT dataSize)
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

Bool FE_DECL FE_ListPushArray_impl(FE_List_impl* list, Byte** data, const void* arrayData, SizeT sizeToPush, SizeT dataSize)
{
	if (!FE_ListCheck(list, data) || arrayData == NULL || sizeToPush <= 0)
	{
		FE_CORE_LOG_ERROR("failed to push array fe_list");
		return FALSE;
	}

	Byte* temp = *data;

	if (list->capacity <= list->count - 1 + sizeToPush)
	{
		if (*data == NULL)
		{
			list->capacity += sizeToPush;
			(*data) = FE_MemoryGeneralAlloc(dataSize * list->capacity);
			list->head = *data;
#ifdef FE_DEBUG
			allocatedListCount++;
#endif
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

	memcpy((*data) + dataSize * list->count, arrayData, dataSize * sizeToPush);
	list->count += sizeToPush;

	return TRUE;
}


Bool FE_DECL FE_ListReserve_impl(FE_List_impl* list, Byte** data, SizeT amount, SizeT dataSize)
{
	if (!FE_ListCheck(list, data))
	{
		FE_CORE_LOG_ERROR("failed to reserve fe_list");
		return FALSE;
	}

	list->capacity += amount;

	Byte* temp = *data;

#ifdef FE_DEBUG
	if(*data == NULL) allocatedListCount++;
#endif

	if ((*data) == NULL)
	{
		(*data) = FE_MemoryGeneralAlloc(dataSize * list->capacity);
		list->head = *data;
	}
	else
	{
		(*data) = FE_MemoryGeneralRealloc((*data), dataSize * list->capacity);
	}

	if ((*data) == NULL)
	{
		(*data) = temp;
		return FALSE;
	}

	return TRUE;
}

Bool FE_ListResize_impl(FE_List_impl* list, Byte** data, SizeT amount, SizeT dataSize)
{
	if (!FE_ListCheck(list, data) || list->count >= amount)
	{
		FE_CORE_LOG_ERROR("failed to resize fe_list");
		return FALSE;
	}

	Bool result = FE_ListReserve_impl(list, data, amount, dataSize);
	if (!result) return result;

	memset((*data) + list->count * dataSize, 0, dataSize * amount);
	list->count += amount;

	return result;
}

Bool FE_DECL FE_ListClear_impl(FE_List_impl* list, Byte** data)
{
	if (!FE_ListCheck(list, data))
	{
		FE_CORE_LOG_ERROR("failed to clear fe_list");
		return FALSE;
	}

	list->capacity = 0;
	list->count = 0;
	if (*data != NULL)
	{
		FE_MemoryGeneralFree(*data);

#ifdef FE_DEBUG
	freedListCount++;
#endif
	}
	return TRUE;
}

Bool FE_ListRemoveDuplicate_impl(FE_List_impl* list, Byte** data, SizeT dataSize)
{
	if (!FE_ListCheck(list, data) || *data == NULL || list->count < 2)
	{
		FE_CORE_LOG_ERROR("failed to remove duplicate");
		return FALSE;
	}

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
				FE_ListRemoveAt_impl(list, data, y, dataSize);
			}
		}
	}

	return TRUE;
}

Bool FE_ListEqual_impl(FE_List_impl* listA, FE_List_impl* listB, Byte** dataA, Byte** dataB, SizeT dataSize)
{
	if (listA != NULL && listB != NULL && listA->isInitialized == TRUE && listB->isInitialized == TRUE)
	{
		FE_CORE_LOG_ERROR("failed to verify equal fe_list");
		return FALSE;
	}

	if (listA == NULL || listB == NULL) return FALSE;

	if (listA->count != listB->count) return FALSE;
	if (dataA == dataB) return TRUE;

	for (SizeT i = 0; i < listA->count; i++)
	{
		if ((*dataA)[i] != (*dataB)[i]) return FALSE;
	}

	return TRUE;
}

Bool FE_DECL FE_ListRemoveAll_impl(FE_List_impl* list)
{
	list->count = 0;
	return TRUE;
}

void FE_DECL FE_ListPrint_impl(const FE_List_impl* list, const Byte* data, SizeT dataSize)
{
	for (SizeT i = 0; i < list->count; i++)
	{
		FE_CORE_LOG_DEBUG("%d", data[dataSize * i]);
	}
}

void FE_ListPrintReport()
{
#ifdef FE_DEBUG
	FE_CORE_LOG_SUCCESS("list report | alloc : %lld        free : %lld", allocatedListCount, freedListCount);

	if (allocatedListCount == freedListCount)
	{
		if (allocatedListCount < freedListCount)
		{
			FE_CORE_LOG_SUCCESS("too much FE_List freed !");
		}
		else
		{
			FE_CORE_LOG_SUCCESS("no memory leak in FE_List detected ! ");
		}
	}
	else
	{
		FE_CORE_LOG_WARNING("memory leak detected");
	}
#endif
}
