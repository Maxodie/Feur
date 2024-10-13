#include "fepch.h"

#include "Feur/Core/LayerStack.h"

void FE_API InitLayerStack(LayerStack* layerStack)
{
	FE_CORE_ASSERT(layerStack, "LayerStacks.c in InitLayerStack is null");

	layerStack->dataPtr = NULL;
	layerStack->count = 0;
}

void FE_API PopLayerStack(LayerStack* layerStack)
{
	FE_CORE_ASSERT(layerStack, "LayerStacks.c in PopLayerStack is null");

	if (layerStack->dataPtr != NULL)
	{
		layerStack->dataPtr[layerStack->count - 1]->OnDetach();

		layerStack->count--;

		if (layerStack->count == 0)
		{
			free(layerStack->dataPtr);
			return;
		}

		Layer** temp = layerStack->dataPtr;
		layerStack->dataPtr = realloc(layerStack->dataPtr, (layerStack->count) * sizeof(Layer)); 
		if (layerStack->dataPtr == NULL) 
		{
			layerStack->dataPtr = temp;
			return;
		}
	}
}

void FE_API InsertLayerStack(LayerStack* layerStack, Layer* value, Uint32 position) {

	FE_CORE_ASSERT(layerStack, "LayerStacks.c in InsertLayerStack is null");
	if (position > layerStack->count) return;

	SizeT i;
	Layer** temp = layerStack->dataPtr;

	layerStack->dataPtr = realloc(layerStack->dataPtr, (layerStack->count + 1) * sizeof(Layer));

	if (layerStack->dataPtr == NULL)
	{
		layerStack->dataPtr = temp;
		return;
	}

	layerStack->count++;
	layerStack->dataPtr[layerStack->count - 1] = NULL;

	for (i = layerStack->count - 1; i >= position; i--)
	{
		layerStack->dataPtr[i] = layerStack->dataPtr[i - 1];
	}

	SizeT positionItemId = (SizeT)position - 1;
	layerStack->dataPtr[positionItemId] = value;

	/*for (i = 0; i < layerStack->count; i++)
	{
		FE_CORE_LOG_ERROR("LayerStack: inserted layer %d | %s ", i, layerStack->dataPtr[i]->layerName)
	}
	*/
}

void FE_API PushLayerStack(LayerStack* layerStack, Layer* value)
{
	FE_CORE_ASSERT(layerStack, "LayerStacks.c in PushLayerStack is null");
	Layer** temp = layerStack->dataPtr;

	layerStack->dataPtr = layerStack->dataPtr == NULL ?
		calloc(layerStack->count + 1, sizeof(Layer)) :
		realloc(layerStack->dataPtr, (layerStack->count + 1) * sizeof(Layer));

	if (layerStack->dataPtr == NULL)
	{
		layerStack->dataPtr = temp;
		return;
	}

	SizeT lastItemId = layerStack->count;
	layerStack->count++;

	layerStack->dataPtr[lastItemId] = value;

	FE_LOG_DEBUG("Add %s layer to the stack", value->layerName);
}
