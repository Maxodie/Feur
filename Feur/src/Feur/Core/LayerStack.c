#include "fepch.h"

#include "Feur/Core/LayerStack.h"

void InitLayerStack(LayerStack* layerStack)
{
	layerStack->dataPtr = NULL;
	layerStack->count = 0;
}

void PopLayerStack(LayerStack* layerStack)
{
	if (layerStack->dataPtr != NULL)
	{
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

		FE_CORE_LOG_DEBUG("test");
	}
}

void InsertLayerStack(LayerStack* layerStack, Layer* value, Uint32 position) {
	size_t i;
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

	layerStack->dataPtr[position - 1] = value;

	for (i = 0; i < layerStack->count; i++)
	{
		FE_CORE_LOG_ERROR("%s ", layerStack->dataPtr[i]->layerName);
	}

}

void PushLayerStack(LayerStack* layerStack, Layer* value)
{
	Layer** temp = layerStack->dataPtr;

	layerStack->dataPtr = layerStack->dataPtr == NULL ?
		calloc(layerStack->count + 1, sizeof(Layer)) :
		realloc(layerStack->dataPtr, (layerStack->count + 1) * sizeof(Layer));

	if (layerStack->dataPtr == NULL)
	{
		layerStack->dataPtr = temp;
		return;
	}

	layerStack->count++;
	layerStack->dataPtr[layerStack->count - 1] = value;
}
