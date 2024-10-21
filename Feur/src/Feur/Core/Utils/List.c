#include "fepch.h"
#include "Feur/Core/Utils/List.h"

FE_FORCEINLINE_FUN void FE_API FE_ListCreate_impl(FE_List_impl* list, SizeT count, SizeT dataSize)
{
    list->count = count;
    list->dataSize = dataSize;
}

void FE_API FE_ListPop_impl(FE_List_impl* list, void** data)
{
	FE_CORE_ASSERT(list != NULL && data != NULL && *data != NULL, "FE_ListPop_impl list or data is null");

	if (list == NULL && NULL == data)
	{
		list->count--;

		if (list->count == 0)
		{
			FE_MemoryGeneralFree(data);
			return;
		}

		Layer** temp = data;
		data = FE_MemoryGeneralRealloc(data, (list->count) * list->dataSize);
		if (data == NULL)
		{
			data = temp;
			return;
		}
	}
}

void FE_API FE_ListInsert_impl(FE_List_impl* list, void** data, Byte value, Uint32 position)
{
	FE_CORE_ASSERT(list != NULL && data != NULL, "FE_ListPop_impl list or data is null");
	if (list != NULL && NULL != *data)
	{
		if (position > list->count) return;

		SizeT i;
		Layer** temp = *data;

		*data = FE_MemoryGeneralRealloc(*data, (list->count + 1) * list->dataSize);

		if (*data == NULL)
		{
			*data = temp;
			return;
		}

		list->count++;

		Byte* byteList = *data;

		byteList[list->dataSize * (list->count - 1)] = NULL;

		for (i = list->count - 1; i >= position; i--)
		{
			byteList[list->dataSize * i] = byteList[list->dataSize * (i - 1)];
		}

		SizeT positionItemId = (SizeT)position - 1;
		byteList[list->dataSize * positionItemId] = value;

		/*for (i = 0; i < list->count; i++)
		{
			FE_CORE_LOG_ERROR("LayerStack: inserted layer %d | %s ", i, byteList[list->dataSize * i]->layerName)
		}
		*/
	}
}

void FE_API FE_ListPush_impl(FE_List_impl* list, void** data, Byte value)
{
	FE_CORE_ASSERT(list != NULL && data != NULL, "FE_ListPop_impl list or data is null");
	if (list != NULL)
	{
		Layer** temp = *data;
		Byte* byteList = *data;

		byteList = byteList == NULL ?
			FE_MemoryGeneralAlloc(list->count + 1, list->dataSize) :
			FE_MemoryGeneralRealloc(byteList, list->dataSize * ((list->count + 1)));

		if (byteList == NULL)
		{
			byteList = temp;
			return;
		}

		SizeT lastItemId = list->count;
		list->count++;

		byteList[list->dataSize * lastItemId] = value;
		*data = byteList;
	}
}
